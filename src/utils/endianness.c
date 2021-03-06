/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   endianness.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/20 15:02:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 18:58:20 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_utils.h"

int			is_big_endian(uint32_t magic_nb)
{
	return (magic_nb == MH_CIGAM || magic_nb == MH_CIGAM_64
	|| magic_nb == FAT_CIGAM);
}

uint64_t	endianness(uint64_t value, int is_big_endian)
{
	if (is_big_endian)
		return (((value & 0xFF) << 24) | (((value >> 8) & 0xFF) << 16) |
	(((value >> 16) & 0xFF) << 8) | ((value >> 24) & 0xFF));
	else
		return (value);
}

void		set_symtab_endianness_32(struct nlist *symtab, uint32_t nsyms,
int is_big_endian)
{
	uint32_t	i;

	i = 0;
	while (i < nsyms)
	{
		symtab[i].n_value = endianness(symtab[i].n_value, is_big_endian);
		symtab[i].n_un.n_strx = endianness(symtab[i].n_un.n_strx,
		is_big_endian);
		i++;
	}
}

void		set_symtab_endianness_64(struct nlist_64 *symtab, uint32_t nsyms,
int is_big_endian)
{
	uint32_t	i;

	i = 0;
	while (i < nsyms)
	{
		symtab[i].n_value = endianness(symtab[i].n_value, is_big_endian);
		symtab[i].n_un.n_strx = endianness(symtab[i].n_un.n_strx,
		is_big_endian);
		i++;
	}
}
