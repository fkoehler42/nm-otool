/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:35:16 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/21 12:14:45 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			init_env_struct(t_nm *env)
{
	const NXArchInfo	*local_arch_info;

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
	if (!(local_arch_info = NXGetLocalArchInfo()))
		env->local_arch = 0;
	else
		env->local_arch = local_arch_info->cputype;
	return (0);
}

void		copy_env_struct(t_nm *src, t_nm *dst)
{
	dst->exec = src->exec;
	dst->file_name = src->file_name;
	dst->file_start = src->file_start;
	dst->file_end = src->file_end;
	dst->opts = src->opts;
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
