/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 10:46:47 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 18:44:55 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	get_sym_type_location_32(uint32_t nsects, struct section *sec_32,
t_sec_location *sections, void *file_end)
{
	uint32_t		i;

	i = 0;
	while (i < nsects)
	{
		if ((void*)sec_32 > file_end)
			return (-1);
		if (ft_strcmp(sec_32->sectname, SECT_TEXT) == 0 &&
		ft_strcmp(sec_32->segname, SEG_TEXT) == 0)
			sections->text = sections->sec_index;
		else if (ft_strcmp(sec_32->sectname, SECT_DATA) == 0 &&
		ft_strcmp(sec_32->segname, SEG_DATA) == 0)
			sections->data = sections->sec_index;
		else if (ft_strcmp(sec_32->sectname, SECT_BSS) == 0 &&
		ft_strcmp(sec_32->segname, SEG_DATA) == 0)
			sections->bss = sections->sec_index;
		sec_32 = (void *)sec_32 + sizeof(*sec_32);
		sections->sec_index++;
		i++;
	}
	return (0);
}

static int	find_sections_32(t_nm *env, uint32_t ncmds, struct load_command *lc,
t_sec_location *sections)
{
	uint32_t				i;
	struct segment_command	*sg;
	struct section			*sec_32;

	i = 0;
	while (i < ncmds)
	{
		if ((void*)lc > env->file_end)
			return (-1);
		if (endianness(lc->cmd, env->big_endian) == LC_SEGMENT)
		{
			sg = (struct segment_command*)lc;
			sec_32 = (struct section*)((void*)sg + sizeof(*sg));
			if (get_sym_type_location_32(endianness(sg->nsects,
			env->big_endian), sec_32, sections, env->file_end) == -1)
				return (-1);
		}
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
		i++;
	}
	return (0);
}

static int	symtab_infos_32(t_nm *env, uint32_t ncmds,
struct symtab_command *symtab_command, struct load_command *lc_start)
{
	t_syminfos		syminfos;
	t_sec_location	sections;

	init_syminfos_struct(&syminfos);
	init_sections_struct(&sections);
	syminfos.nsyms = endianness(symtab_command->nsyms, env->big_endian);
	syminfos.stringtab = env->file_start +
	endianness(symtab_command->stroff, env->big_endian);
	syminfos.symtab_32 = env->file_start +
	endianness(symtab_command->symoff, env->big_endian);
	if (syminfos.stringtab > env->file_end ||
	(void*)syminfos.symtab_32 > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	if ((find_sections_32(env, ncmds, lc_start, &sections)) == -1)
		return (put_error(MALFORMED, env->exec, env->file_name));
	set_symtab_endianness_32(syminfos.symtab_32, syminfos.nsyms,
	env->big_endian);
	print_32(env, &syminfos, &sections);
	return (0);
}

int			handle_32(t_nm *env)
{
	uint32_t				i;
	struct mach_header		*header;
	struct load_command		*lc_start;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header*)env->file_start;
	lc_start = (struct load_command*)(env->file_start + sizeof(*header));
	lc = lc_start;
	header->ncmds = endianness(header->ncmds, env->big_endian);
	while (i < header->ncmds)
	{
		if ((void*)lc > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (endianness(lc->cmd, env->big_endian) == LC_SYMTAB)
		{
			if (symtab_infos_32(env, header->ncmds,
			(struct symtab_command*)lc, lc_start) == -1)
				return (-1);
			break ;
		}
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	return (0);
}
