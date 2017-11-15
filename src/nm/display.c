/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:10:45 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 11:40:10 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_sym_32(uint32_t value, char type, char *str)
{
	if (!value)
		ft_printf("%8c %c %s\n", ' ', type, str);
	else
		ft_printf("%08llx %c %s\n", value, type, str);
}

static void	print_sym_64(uint64_t value, char type, char *str)
{
	if (!value)
		ft_printf("%16c %c %s\n", ' ', type, str);
	else
		ft_printf("%016llx %c %s\n", value, type, str);
}

void		print_32(struct nlist *symtab, void *stringtab,
		t_sec_location *sections, uint32_t nsyms)
{
	uint32_t	i;
	char		sym_type;

	ascii_sort_32(symtab, stringtab, nsyms);
	i = 0;
	while (i < nsyms)
	{
		sym_type = get_sym_type(symtab[i].n_type, symtab[i].n_sect,
		(uint64_t)symtab[i].n_value, sections);
		print_sym_32(symtab[i].n_value, sym_type,
		(char*)(stringtab + symtab[i].n_un.n_strx));
		i++;
	}
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
		print_sym_64(symtab[i].n_value, sym_type,
				(char*)(stringtab + symtab[i].n_un.n_strx));
		i++;
	}
}