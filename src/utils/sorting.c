/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sorting.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 18:00:33 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/13 19:24:57 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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
}
