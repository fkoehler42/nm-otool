/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:35:16 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 14:06:27 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int			init_env_struct(t_executable exec)
{
	t_nm_otool	*env;

	if (!(env = (t_nm_otool*)malloc(sizeof(*env))))
		return (put_error(MALLOC, exec, NULL));
	env->file_size = 0;
	get_env_struct(env);
	return (0);
}

t_nm_otool	*get_env_struct(t_nm_otool *env)
{
	static t_nm_otool	*env_save = NULL;

	if (env != NULL)
		env_save = env;
	return (env_save);
}
