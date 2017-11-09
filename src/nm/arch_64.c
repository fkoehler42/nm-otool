/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 19:26:35 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
/* WIP
static int	nm_syms_type(t_nm_otool *env)
{
	struct segment_command	*sc;

	sc = env->file_start +
	sizeof(struct mach_header_64) + sizeof(struct load_command);
	if ((void*)sc > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	ft_put_uintmax(sc->nsects, 10);
	return (0);
}
WIP */
static int	nm_syms_infos_64(t_nm_otool *env,
struct symtab_command *symtab_command)
{
	int				i;
	int				nsyms;
	void			*stringtable;
	struct nlist_64	*symtable;

	i = 0;
	nsyms = (int)symtab_command->nsyms;
	stringtable = env->file_start + symtab_command->stroff;
	symtable = env->file_start + symtab_command->symoff;
	if (stringtable > env->file_end || (void*)symtable > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	ascii_sort_64(stringtable, symtable, nsyms);
	nm_syms_type(env);
	while (i < nsyms)
	{
		if (!symtable[i].n_value)
		{
			ft_printf("%16c %s\n", ' ',
			(char*)stringtable + symtable[i].n_un.n_strx);
		}
		else
		{
			ft_printf("%016llx %s\n", symtable[i].n_value,
			(char*)stringtable + symtable[i].n_un.n_strx);
		}
		i++;
	}
	return (0);
}

int			nm_handle_64(t_nm_otool *env)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64*)env->file_start;
	ncmds = header->ncmds;
	lc = env->file_start + sizeof(*header);
	while (i < ncmds)
	{
		if ((void*)lc > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (lc->cmd == LC_SYMTAB)
		{
			nm_syms_infos_64(env, (struct symtab_command*)lc);
			break;
		}
		i++;
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}
