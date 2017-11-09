/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 16:41:45 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void	nm_output_64(t_nm_otool *env, struct symtab_command *symtab_command)
{
	int				i;
	int				nsyms;
	void			*stringtable;
	struct nlist_64	*symtable;

	i = 0;
	nsyms = (int)symtab_command->nsyms;
	stringtable = env->file_start + symtab_command->stroff;
	symtable = env->file_start + symtab_command->symoff;
	ascii_sort_64(stringtable, symtable, nsyms);
	while (i < nsyms)
	{
		ft_putendl(stringtable + symtable[i].n_un.n_strx);
		i++;
	}
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
	if ((void*)lc > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			nm_output_64(env, (struct symtab_command*)lc);
			break;
		}
		i++;
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}
