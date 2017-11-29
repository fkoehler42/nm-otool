/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 16:19:55 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int get_sections_64(t_otool *env, struct load_command *lc)
{
	uint32_t					i;
	struct segment_command_64	*sg;
	struct section_64			*sec_64;

	i = 0;
	sg = (struct segment_command_64*)lc;
	sg->nsects = endianness(sg->nsects, env->big_endian);
	sec_64 = (struct section_64*)((void*)sg + sizeof(*sg));
	while (i < sg->nsects)
	{
		if ((void*)sec_64 > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (!ft_strcmp(sec_64->sectname, SECT_TEXT) &&
		!ft_strcmp(sec_64->segname, SEG_TEXT))
		{
			if (set_section_64_endianness(env, sec_64) == -1)
				return (put_error(MALFORMED, env->exec, env->file_name));
			print_section_64(env, sec_64);
		}
		i++;
		sec_64 = (void*)sec_64 + sizeof(*sec_64);
	}
	return (0);
}

int			handle_64(t_otool *env)
{
	uint32_t					i;
	struct mach_header_64		*header;
	struct load_command			*lc;

	i = 0;
	header = (struct mach_header_64*)env->file_start;
	lc = (struct load_command*)(env->file_start + sizeof(*header));
	header->ncmds = endianness(header->ncmds, env->big_endian);
	while (i < header->ncmds)
	{
		if ((void*)lc > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (endianness(lc->cmd, env->big_endian) == LC_SEGMENT_64)
		{
			if (get_sections_64(env, lc) == -1)
				return (-1);
		}
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	return (0);
}
