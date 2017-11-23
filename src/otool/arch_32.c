/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 19:57:54 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"
/*
static int	get_sym_type_location_64(uint32_t nsects, struct section_64 *sec_64,
t_sec_location *sections, void *file_end)
{
	uint32_t		i;

	i = 0;
	while (i < nsects)
	{
		if ((void*)sec_64 > file_end)
			return (-1);
		if (ft_strcmp(sec_64->sectname, SECT_TEXT) == 0 &&
		ft_strcmp(sec_64->segname, SEG_TEXT) == 0)
			sections->text = sections->sec_index;
		else if (ft_strcmp(sec_64->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sec_64->segname, SEG_DATA) == 0)
			sections->data = sections->sec_index;
		else if (ft_strcmp(sec_64->sectname, SECT_BSS) == 0 &&
		ft_strcmp(sec_64->segname, SEG_DATA) == 0)
			sections->bss = sections->sec_index;
		sec_64 = (void *)sec_64 + sizeof(*sec_64);
		sections->sec_index++;
		i++;
	}
	return (0);
}

static int	find_sections_64(t_otool *env, uint32_t ncmds, struct load_command *lc,
t_sec_location *sections)
{
	uint32_t					i;
	struct segment_command_64	*sg;
	struct section_64			*sec_64;

	i = 0;
	while (i < ncmds)
	{
		if ((void*)lc > env->file_end)
			return (-1);
		if (endianness(lc->cmd, env->big_endian) == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64*)lc;
			sec_64 = (struct section_64*)((void*)sg + sizeof(*sg));
			if (get_sym_type_location_64(endianness(sg->nsects, env->big_endian),
			sec_64, sections, env->file_end) == -1)
				return (-1);
		}
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
		i++;
	}
	return (0);
}
*/

static int get_sections_32(t_otool *env, struct load_command *lc)
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
		if ((void*)sec_64 > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (ft_strcmp(sec_64->sectname, SECT_TEXT) == 0 &&
		ft_strcmp(sec_64->segname, SEG_TEXT) == 0)
		{
			ft_putendl(env->file_name);
			print_section_64(sec_64->sectname, sec_64->addr, sec_64->size,
			(unsigned char*)(env->file_start + sec_64->offset));
		}
		i++;
		sec_64++;
	}
	return (0);
}

int			handle_32(t_otool *env)
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
			if (get_sections_32(env, lc) == -1)
				return (-1);
			break;
		}
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	return (0);
}
