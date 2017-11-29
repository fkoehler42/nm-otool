/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:32:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 13:28:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static void	print_byte_value(uint8_t byte)
{
	if (byte == 0)
		ft_putstr("00 ");
	else
	{
		if (byte < 16)
			ft_putchar('0');
		ft_put_uintmax(byte, 16);
		ft_putchar(' ');
	}
}

void		print_infos(char *file_name, cpu_type_t arch, int multiple_arch)
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
		ft_printf("%s (architecture %s):\n", file_name, arch_name);
	}
	else
		ft_printf("%s:\n", file_name);
}

void		print_section_32(char *sec_name, uint32_t sec_addr,
uint32_t sec_size, uint8_t *content)
{
	uint32_t	i;

	i = 0;
	ft_printf("Contents of (%s,", ft_strupper(sec_name));
	ft_printf("%s) section\n", ft_strlower(sec_name));
	while (i < sec_size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				sec_addr += 16;
			ft_printf("%08lx\t", sec_addr);
		}
		print_byte_value(*content);
		if ((++i % 16) == 0 && i < sec_size)
			ft_putchar('\n');
		content++;
	}
	if (i > 0)
		ft_putchar('\n');
}

void		print_section_64(char *sec_name, uint64_t sec_addr,
uint64_t sec_size, uint8_t *content)
{
	uint64_t	i;

	i = 0;
	ft_printf("Contents of (%s,", ft_strupper(sec_name));
	ft_printf("%s) section\n", ft_strlower(sec_name));
	while (i < sec_size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				sec_addr += 16;
			ft_printf("%016llx\t", sec_addr);
		}
		print_byte_value(*content);
		if ((++i % 16) == 0 && i < sec_size)
			ft_putchar('\n');
		content++;
	}
	if (i > 0)
		ft_putchar('\n');
}
