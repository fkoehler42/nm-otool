/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   section_endianness.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 14:52:22 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 15:55:11 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int		set_section_32_endianness(t_otool *env, struct section *sec)
{
	uint32_t	i;
	uint32_t	sec_addr_cpy;
	void		*sec_content;

	i = 0;
	if ((void*)sec->sectname > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	sec->size = (uint32_t)endianness((uint64_t)sec->size, env->big_endian);
	sec->offset = (uint32_t)endianness((uint64_t)sec->offset, env->big_endian);
	sec->addr = (uint32_t)endianness((uint64_t)sec->addr, env->big_endian);
	sec_content = env->file_start + sec->offset;
	sec_addr_cpy = sec->addr;
	while (i < sec->size)
	{
		if (sec_content > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if ((i != 0) && (i % 16 == 0))
			sec_addr_cpy += 16;
		sec_content++;
		i++;
	}
	return (0);
}

int		set_section_64_endianness(t_otool *env, struct section_64 *sec)
{
	uint64_t	i;
	uint64_t	sec_addr_cpy;
	void		*sec_content;

	i = 0;
	if ((void*)sec->sectname > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	sec->size = endianness(sec->size, env->big_endian);
	sec->offset = (uint32_t)endianness((uint64_t)sec->offset, env->big_endian);
	sec->addr = endianness(sec->addr, env->big_endian);
	sec_content = env->file_start + sec->offset;
	sec_addr_cpy = sec->addr;
	while (i < sec->size)
	{
		if (sec_content > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if ((i != 0) && (i % 16 == 0))
			sec_addr_cpy += 16;
		sec_content++;
		i++;
	}
	return (0);
}
