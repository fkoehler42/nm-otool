/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_sorting.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 18:35:53 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 18:58:38 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_utils.h"

void	sort_symtab(t_syminfos *syminfos, t_opts *opts)
{
	if (opts->p)
		return ;
	if (syminfos->symtab_32)
	{
		if (opts->r)
			rev_ascii_sort_32(syminfos->symtab_32, syminfos->stringtab,
			syminfos->nsyms);
		else
			ascii_sort_32(syminfos->symtab_32, syminfos->stringtab,
			syminfos->nsyms);
	}
	else if (syminfos->symtab_64)
	{
		if (opts->r)
			rev_ascii_sort_64(syminfos->symtab_64, syminfos->stringtab,
			syminfos->nsyms);
		else
			ascii_sort_64(syminfos->symtab_64, syminfos->stringtab,
			syminfos->nsyms);
	}
}

void	asc_sort_offset_array(uint32_t *array, uint32_t array_len)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	tmp;

	i = 0;
	while (i < array_len - 1)
	{
		j = i + 1;
		while (j < array_len)
		{
			if (array[i] > array[j])
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
}
