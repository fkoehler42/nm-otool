/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:10:45 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/21 15:51:09 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_sym_32(uint32_t value, char type, char *str)
{
	if (!ft_strcmp(str, "radr://5614542") || type == '-')
		return ;
	if (!value && (type == 'u' || type == 'U'))
		ft_printf("%8c %c %s\n", ' ', type, str);
	else
		ft_printf("%08lx %c %s\n", value, type, str);
}

static void	print_sym_64(uint64_t value, char type, char *str)
{
	if (!ft_strcmp(str, "radr://5614542") || type == '-')
		return ;
	if (!value && (type == 'u' || type == 'U'))
		ft_printf("%16c %c %s\n", ' ', type, str);
	else
		ft_printf("%016llx %c %s\n", value, type, str);
}

void		print_32(t_nm *env, t_syminfos *syminfos, t_sec_location *sections)
{
	uint32_t	i;
	char		sym_type;

	i = 0;
	(void)env;
	ascii_sort_32(syminfos->symtab_32, syminfos->stringtab,
	syminfos->nsyms);
	while (i < syminfos->nsyms)
	{
		sym_type = get_sym_type(syminfos->symtab_32[i].n_type,
		syminfos->symtab_32[i].n_sect,
		(uint64_t)syminfos->symtab_32[i].n_value, sections);
		print_sym_32(syminfos->symtab_32[i].n_value, sym_type,
		(char*)(syminfos->stringtab + syminfos->symtab_32[i].n_un.n_strx));
		i++;
	}
}

void		print_64(t_nm *env, t_syminfos *syminfos, t_sec_location *sections)
{
	uint32_t	i;
	char		sym_type;

	i = 0;
	(void)env;
	ascii_sort_64(syminfos->symtab_64, syminfos->stringtab,
	syminfos->nsyms);
	while (i < syminfos->nsyms)
	{
		sym_type = get_sym_type(syminfos->symtab_64[i].n_type,
		syminfos->symtab_64[i].n_sect,
		syminfos->symtab_64[i].n_value, sections);
		print_sym_64(syminfos->symtab_64[i].n_value, sym_type,
		(char*)(syminfos->stringtab + syminfos->symtab_64[i].n_un.n_strx));
		i++;
	}
}
