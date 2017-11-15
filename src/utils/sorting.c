/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:00:33 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 12:32:42 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	ascii_sort_duplicates_32(struct nlist *array, void *stringtable,
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
			(array[i].n_value > array[j].n_value))
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

static void	ascii_sort_duplicates_64(struct nlist_64 *array, void *stringtable,
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
			(array[i].n_value > array[j].n_value))
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

void	ascii_sort_32(struct nlist *array, void *stringtable, int nb_elem)
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
			stringtable + array[j].n_un.n_strx) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
	ascii_sort_duplicates_32(array, stringtable, nb_elem);
}

void	ascii_sort_64(struct nlist_64 *array, void *stringtable, int nb_elem)
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
			stringtable + array[j].n_un.n_strx) > 0)
			{
				tmp = array[i];
				array[i] = array[j];
				array[j] = tmp;
			}
			j++;
		}
		i++;
	}
	ascii_sort_duplicates_64(array, stringtable, nb_elem);
}
