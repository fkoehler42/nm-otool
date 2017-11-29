/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:32:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 16:44:53 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	print_byte_value(uint8_t byte, uint64_t byte_index, cpu_type_t arch)
{
	if (byte < 16)
		ft_putchar('0');
	ft_put_uintmax(byte, 16);
	if (((arch != CPU_TYPE_POWERPC) && (arch != CPU_TYPE_POWERPC64)) ||
	(((arch == CPU_TYPE_POWERPC) || (arch == CPU_TYPE_POWERPC64)) &&
	(byte_index != 0) && (++byte_index % 4 == 0)))
		ft_putchar(' ');
}

static void	print_infos(char *file_name, cpu_type_t arch, int multiple_arch,
char *sec_name)
{
	char	*arch_name;

	arch_name = NULL;
	if (multiple_arch && arch)
	{
		if (arch == CPU_TYPE_I386)
			arch_name = "i386";
		else if (arch == CPU_TYPE_X86)
			arch_name = "x86";
		else if (arch == CPU_TYPE_POWERPC)
			arch_name = "ppc";
		else if (arch == CPU_TYPE_POWERPC64)
			arch_name = "ppc64";
		ft_printf("%s (architecture %s):\nContents of (%s,",
		file_name, arch_name, ft_strupper(sec_name));
		ft_printf("%s) section\n", ft_strlower(sec_name));
	}
	else
	{
		if (arch != -1)
			ft_printf("%s:\n", file_name);
		ft_printf("Contents of (%s,", ft_strupper(sec_name));
		ft_printf("%s) section\n", ft_strlower(sec_name));
	}
}

void		print_section_32(t_otool *env, struct section *sec)
{
	uint32_t	i;
	uint8_t		*sec_content;

	i = 0;
	sec_content = (uint8_t*)(env->file_start + sec->offset);
	print_infos(env->file_name, env->current_arch, env->multiple_arch,
	sec->sectname);
	while (i < sec->size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				sec->addr += 16;
			ft_printf("%08lx\t", sec->addr);
		}
		print_byte_value(*sec_content, (uint64_t)i, env->current_arch);
		if ((++i % 16) == 0 && i < sec->size)
			ft_putchar('\n');
		sec_content++;
	}
	if (i > 0)
		ft_putchar('\n');
}

void		print_section_64(t_otool *env, struct section_64 *sec)
{
	uint64_t	i;
	uint8_t		*sec_content;

	i = 0;
	sec_content = (uint8_t*)(env->file_start + sec->offset);
	print_infos(env->file_name, env->current_arch, env->multiple_arch,
	sec->sectname);
	while (i < sec->size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				sec->addr += 16;
			ft_printf("%016llx\t", sec->addr);
		}
		print_byte_value(*sec_content, i, env->current_arch);
		if ((++i % 16) == 0 && i < sec->size)
			ft_putchar('\n');
		sec_content++;
	}
	if (i > 0)
		ft_putchar('\n');
}
