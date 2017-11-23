/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 20:27:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int get_sections_64(t_otool *env, struct load_command *lc)
{
	uint32_t					i;
	struct segment_command_64	*sg;
	struct section_64			*sec_64;

	sg = (struct segment_command_64*)lc;
	sg->nsects = endianness(sg->nsects, env->big_endian);
	sec_64 = (struct section_64*)((void*)sg + sizeof(*sg));

	i = 0;
	while (i < sg->nsects)
	{
		debug
		if ((void*)sec_64 > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (!ft_strcmp(sec_64->sectname, SECT_TEXT) &&
		!ft_strcmp(sec_64->segname, SEG_TEXT))
		{
			ft_putendl(env->file_name);
			print_section_64(sec_64->sectname, sec_64->addr, sec_64->size,
			(unsigned char*)(env->file_start + sec_64->offset));
		}
		i++;
		sec_64 = (void *)sec_64 + sizeof(*sec_64);
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
			break;
		}
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	return (0);
}