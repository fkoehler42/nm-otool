/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:35:16 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 16:13:42 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

void	init_env_struct(t_nm_otool *env)
{
	env->file_start = NULL;
	env->file_end = NULL;
}
/*
t_nm_otool	*get_env_struct(t_nm_otool *env)
{
	static t_nm_otool	*env_save = NULL;

	if (env != NULL)
		env_save = env;
	return (env_save);
}
*/
