/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rev_ascii_sorting.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/22 15:06:13 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 16:12:02 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool_utils.h"

static void	rev_ascii_sort_duplicates_32(struct nlist *array, void *stringtable,
		int nb_elem)
{
	int				i;
	int				j;
	struct nlist	tmp;

	i = 0;
	while (i < nb_elem - 1)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			if (!ft_strcmp(stringtable + array[i].n_un.n_strx,
			stringtable + array[j].n_un.n_strx) &&
			(array[i].n_value < array[j].n_value))
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

static void	rev_ascii_sort_duplicates_64(struct nlist_64 *array, void *stringtable,
		int nb_elem)
{
	int				i;
	int				j;
	struct nlist_64	tmp;

	i = 0;
	while (i < nb_elem - 1)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			if (!ft_strcmp(stringtable + array[i].n_un.n_strx,
			stringtable + array[j].n_un.n_strx) &&
			(array[i].n_value < array[j].n_value))
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

void	rev_ascii_sort_32(struct nlist *array, void *stringtable, int nb_elem)
{
	int				i;
	int				j;
	struct nlist	tmp;

	i = 0;
	while (i < nb_elem - 1)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			if (ft_strcmp(stringtable + array[i].n_un.n_strx,
			stringtable + array[j].n_un.n_strx) < 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
	rev_ascii_sort_duplicates_32(array, stringtable, nb_elem);
}

void	rev_ascii_sort_64(struct nlist_64 *array, void *stringtable, int nb_elem)
{
	int				i;
	int				j;
	struct nlist_64	tmp;

	i = 0;
	while (i < nb_elem - 1)
	{
		j = i + 1;
		while (j < nb_elem)
		{
			if (ft_strcmp(stringtable + array[i].n_un.n_strx,
			stringtable + array[j].n_un.n_strx) < 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
	rev_ascii_sort_duplicates_64(array, stringtable, nb_elem);
}
