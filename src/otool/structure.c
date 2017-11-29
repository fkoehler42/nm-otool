/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 17:16:00 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 18:22:46 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void		init_env_struct(t_otool *env)
{
	env->exec = EXEC_OTOOL;
	env->file_name = NULL;
	env->file_start = NULL;
	env->file_end = NULL;
	env->opt_data = 0;
	env->printed = 0;
	env->local_arch = CPU_TYPE_X86_64;
	env->current_arch = 0;
	env->multiple_arch = 0;
	env->big_endian = 0;
}

void		update_env_struct(t_otool *env, char *arg)
{
	env->file_name = arg;
	env->file_start = NULL;
	env->file_end = NULL;
	env->printed = 0;
	env->current_arch = 0;
	env->multiple_arch = 0;
	env->big_endian = 0;
}

void		copy_env_struct(t_otool *src, t_otool *dst)
{
	dst->exec = src->exec;
	dst->file_name = src->file_name;
	dst->file_start = src->file_start;
	dst->file_end = src->file_end;
	dst->opt_data = src->opt_data;
	dst->printed = src->printed;
	dst->local_arch = src->local_arch;
	dst->current_arch = 0;
	dst->multiple_arch = src->multiple_arch;
	dst->big_endian = src->big_endian;
}
