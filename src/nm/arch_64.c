/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_64.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 14:15:30 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/13 19:32:19 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

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

static int	find_sections_64(uint32_t ncmds, struct load_command *lc,
t_sec_location *sections, void *file_end)
{
	uint32_t					i;
	struct segment_command_64	*sg;
	struct section_64			*sec_64;

	i = 0;
	while (i < ncmds)
	{
		if ((void*)lc > file_end)
			return (-1);
		if (lc->cmd == LC_SEGMENT_64)
		{
			sg = (struct segment_command_64*)lc;
			sec_64 = (struct section_64*)((void*)sg + sizeof(*sg));
			if (get_sym_type_location_64(sg->nsects, sec_64, sections,
			file_end) == -1)
				return (-1);
		}
		lc = (void*)lc + lc->cmdsize;
		i++;
	}
	return (0);
}
/*
static int	symtab_64(t_nm *env, int nsyms, void *stringtable,
		struct nlist_64 *symtable)
{
	int			i;

	i = 0;
	if (!(env->symt_array = create_symt_array(nsyms, env->exec)))
		return (-1);
	while (env->symt_array[i])
	{
		if (symtable[i].n_value)
			env->symt_array[i]->value = (uintmax_t)symtable[i].n_value;
		env->symt_array[i]->str = (char*)stringtable;
		i++;
	}
	return (0);
}
*/
static int	symtab_infos_64(t_nm *env, uint32_t ncmds,
struct symtab_command *symtab_command, struct load_command *lc_start)
{
	/* uint32_t		nsyms; */
	void			*stringtable;
	struct nlist_64	*symtable;
	t_sec_location	sections;

	/* nsyms = (int)symtab_command->nsyms; */
	stringtable = env->file_start + symtab_command->stroff;
	symtable = env->file_start + symtab_command->symoff;
	init_sections_struct(&sections);
	if (stringtable > env->file_end || (void*)symtable > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	if ((find_sections_64(ncmds, lc_start, &sections, env->file_end)) == -1)
		return (put_error(MALFORMED, env->exec, env->file_name));
	print_64(symtable, stringtable, &sections, symtab_command->nsyms);
	return (0);
}

int			handle_64(t_nm *env)
{
	uint32_t				i;
	struct mach_header_64	*header;
	struct load_command		*lc_start;
	struct load_command		*lc;

	i = 0;
	header = (struct mach_header_64*)env->file_start;
	lc_start = (struct load_command*)(env->file_start + sizeof(*header));
	lc = lc_start;
	while (i < header->ncmds)
	{
		if ((void*)lc > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (lc->cmd == LC_SYMTAB)
		{
			if (symtab_infos_64(env, header->ncmds,
			(struct symtab_command*)lc, lc_start) == -1)
				return (-1);
			break;
		}
		lc = (void*)lc + lc->cmdsize;
	}
	return (0);
}
