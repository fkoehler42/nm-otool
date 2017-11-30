/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/30 14:51:35 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

int			check_load_command_overflow(t_otool *env, struct load_command *lc,
uint32_t ncmds)
{
	uint32_t	i;

	i = 0;
	while (i < ncmds)
	{
		if ((void*)lc > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	return (0);
}

int			is_sought_section(char *sec_name, char *seg_name, int option_data)
{
	char *sought_sec_name;
	char *sought_seg_name;

	sought_sec_name = option_data ? SECT_DATA : SECT_TEXT;
	sought_seg_name = option_data ? SEG_DATA : SEG_TEXT;
	if (!ft_strcmp(sec_name, sought_sec_name) &&
	!ft_strcmp(seg_name, sought_seg_name))
		return (1);
	return (0);
}

static int	browse_sections_64(t_otool *env, struct load_command *lc)
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
		if (is_sought_section(sec_64->sectname, sec_64->segname,
		env->opt_data))
		{
			if (set_section_64_endianness(env, sec_64) == -1)
				return (put_error(MALFORMED, env->exec, env->file_name));
			env->printed = 1;
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
	if (check_load_command_overflow(env, lc, header->ncmds) == -1)
		return (-1);
	while (i < header->ncmds)
	{
		if (endianness(lc->cmd, env->big_endian) == LC_SEGMENT_64)
		{
			if (browse_sections_64(env, lc) == -1)
				return (-1);
		}
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	if (!env->printed && env->current_arch != -1)
		ft_printf("%s:\n", env->file_name);
	return (0);
}
