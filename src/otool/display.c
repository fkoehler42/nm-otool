/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:32:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 12:22:54 by fkoehler         ###   ########.fr       */
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

void		print_section_64(char *sec_name, uint64_t sec_addr,
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
			ft_printf("%016llx\t", sec_addr);
		}
		print_byte_value(*content);
		if ((++i % 16) == 0 && i < sec_size)
			ft_putchar('\n');
		content++;
	}
	ft_putchar('\n');
}
