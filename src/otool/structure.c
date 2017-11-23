/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 17:16:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 20:21:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int			init_env_struct(t_otool *env)
{
	env->exec = EXEC_OTOOL;
	env->file_name = NULL;
	env->file_start = NULL;
	env->file_end = NULL;
	if (!(env->opts = (t_opts*)malloc(sizeof(*env->opts))))
		return (put_error(MALLOC, env->exec, NULL));
	env->opts->p = 0;
	env->opts->r = 0;
	env->opts->u = 0;
	env->opts->U = 0;
	env->opts->j = 0;
	env->big_endian = 0;
	return (0);
}
