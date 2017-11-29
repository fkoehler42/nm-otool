/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_32.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:30:02 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 18:50:10 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	get_sections_32(t_otool *env, struct load_command *lc)
{
	uint32_t					i;
	struct segment_command		*sg;
	struct section				*sec_32;

	i = 0;
	sg = (struct segment_command*)lc;
	sg->nsects = endianness(sg->nsects, env->big_endian);
	sec_32 = (struct section*)((void*)sg + sizeof(*sg));
	while (i < sg->nsects)
	{
		if ((void*)sec_32 > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (is_sought_section(sec_32->sectname, sec_32->segname,
		env->opt_data))
		{
			if (set_section_32_endianness(env, sec_32) == -1)
				return (put_error(MALFORMED, env->exec, env->file_name));
			env->printed = 1;
			print_section_32(env, sec_32);
		}
		i++;
		sec_32 = (void*)sec_32 + sizeof(*sec_32);
	}
	return (0);
}

int			handle_32(t_otool *env)
{
	uint32_t			i;
	struct mach_header	*header;
	struct load_command	*lc;

	i = 0;
	header = (struct mach_header*)env->file_start;
	lc = (struct load_command*)(env->file_start + sizeof(*header));
	header->ncmds = endianness(header->ncmds, env->big_endian);
	while (i < header->ncmds)
	{
		if ((void*)lc > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (endianness(lc->cmd, env->big_endian) == LC_SEGMENT)
		{
			if (get_sections_32(env, lc) == -1)
				return (-1);
		}
		i++;
		lc = (void*)lc + endianness(lc->cmdsize, env->big_endian);
	}
	if (!env->printed && env->current_arch != -1)
		ft_printf("%s:\n", env->file_name);
	return (0);
}
