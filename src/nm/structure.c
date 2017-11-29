/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:35:16 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 19:11:43 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			init_env_struct(t_nm *env)
{
	env->exec = EXEC_NM;
	env->file_name = NULL;
	env->file_start = NULL;
	env->file_end = NULL;
	if (!(env->opts = (t_opts*)malloc(sizeof(*env->opts))))
		return (put_error(MALLOC, env->exec, NULL));
	env->opts->p = 0;
	env->opts->r = 0;
	env->opts->u = 0;
	env->opts->uu = 0;
	env->opts->j = 0;
	env->local_arch = CPU_TYPE_X86_64;
	env->current_arch = 0;
	env->multiple_arg = 0;
	env->multiple_arch = 0;
	env->big_endian = 0;
	return (0);
}

void		update_env_struct(t_nm *env, char *arg)
{
	env->file_name = arg;
	env->file_start = NULL;
	env->file_end = NULL;
	env->current_arch = 0;
	env->multiple_arch = 0;
	env->big_endian = 0;
}

void		copy_env_struct(t_nm *src, t_nm *dst)
{
	dst->exec = src->exec;
	dst->file_name = src->file_name;
	dst->file_start = src->file_start;
	dst->file_end = src->file_end;
	dst->opts = src->opts;
	dst->local_arch = src->local_arch;
	dst->current_arch = 0;
	dst->multiple_arg = src->multiple_arg;
	dst->multiple_arch = src->multiple_arch;
	dst->big_endian = src->big_endian;
}

void		init_syminfos_struct(t_syminfos *syminfos)
{
	syminfos->stringtab = NULL;
	syminfos->symtab_32 = NULL;
	syminfos->symtab_64 = NULL;
	syminfos->nsyms = 0;
}

void		init_sections_struct(t_sec_location *sections)
{
	sections->bss = 0;
	sections->data = 0;
	sections->text = 0;
	sections->sec_index = 1;
}
