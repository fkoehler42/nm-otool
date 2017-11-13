/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:10:45 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/13 20:00:42 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_sym(uint64_t value, char type, char *str)
{
	if (!value)
		ft_printf("%16c %c %s\n", ' ', type, str);
	else
		ft_printf("%016llx %c %s\n", value, type, str);
}

void		print_64(struct nlist_64 *symtab, void *stringtab,
		t_sec_location *sections, uint32_t nsyms)
{
	uint32_t	i;
	char		sym_type;

	ascii_sort_64(symtab, stringtab, nsyms);
	i = 0;
	while (i < nsyms)
	{
		sym_type = get_sym_type(symtab[i].n_type, symtab[i].n_sect,
				symtab[i].n_value, sections);
		print_sym(symtab[i].n_value, sym_type,
				(char*)(stringtab + symtab[i].n_un.n_strx));
		i++;
	}
}
