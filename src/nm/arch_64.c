/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/08 19:26:06 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

static void	nm_output_64(void *file_ptr, struct symtab_command *symtab_command)
{
	int				i;
	int				nsyms;
	void			*stringtable;
	struct nlist_64	*symtable;

	i = 0;
	nsyms = (int)symtab_command->nsyms;
	stringtable = file_ptr + symtab_command->stroff;
	symtable = file_ptr + symtab_command->symoff;
	standard_sort_64(stringtable, symtable, nsyms);
	while (i < nsyms)
	{
		ft_putendl(stringtable + symtable[i].n_un.n_strx);
		i++;
	}
}

void		nm_handle_64(void *file_ptr)
{
	int						i;
	int						ncmds;
	struct mach_header_64	*header;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64*)file_ptr;
	ncmds = header->ncmds;
	lc = file_ptr + sizeof(*header);
	while (i < ncmds)
	{
		if (lc->cmd == LC_SYMTAB)
		{
			nm_output_64(file_ptr, (struct symtab_command*)lc);
			break;
		}
		i++;
		lc = (void*)lc + lc->cmdsize;
	}
}
