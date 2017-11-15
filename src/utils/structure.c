/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:35:16 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 16:21:57 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		init_env_struct(t_nm *env)
{
	env->file_name = NULL;
	env->file_start = NULL;
	env->file_end = NULL;
	env->big_endian = 0;
}

void		copy_env_struct(t_nm *src, t_nm *dst)
{
	dst->exec = src->exec;
	dst->file_name = src->file_name;
	dst->file_start = src->file_start;
	dst->file_end = src->file_end;
	dst->big_endian = src->big_endian;
}

void		init_sections_struct(t_sec_location *sections)
{
	sections->bss = 0;
	sections->data = 0;
	sections->text = 0;
	sections->sec_index = 1;
}
