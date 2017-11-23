/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   overflow_protection.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:12:35 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 16:12:39 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			check_stringtab_validity_32(t_nm *env, struct nlist *array,
void *stringtab, int nb_elem)
{
	int		i;

	i = 0;
	while (i < nb_elem)
	{
		if ((void*)(stringtab + array[i].n_un.n_strx) > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		i++;
	}
	return (0);
}

int			check_stringtab_validity_64(t_nm *env, struct nlist_64 *array,
void *stringtab, int nb_elem)
{
	int		i;

	i = 0;
	while (i < nb_elem)
	{
		if ((void*)(stringtab + array[i].n_un.n_strx) > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		i++;
	}
	return (0);
}
