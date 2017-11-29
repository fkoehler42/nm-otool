/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 18:32:44 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 12:01:52 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

void	print_section_64(char *sec_name, uint64_t sec_addr, uint32_t sec_size,
unsigned char *content)
{
	uint32_t	i;

	i = 0;
	ft_printf("Contents of (%s,%s) section\n", ft_strupper(sec_name),
	ft_strlower(sec_name));
	while (i < sec_size)
	{
		if (i == 0 || i % 16 == 0)
		{
			if (i != 0)
				sec_addr += 16;
			ft_printf("%016llx\t", sec_addr);
		}
		if (*content == 0)
			ft_putstr("00 ");
		else
		{
			if (*content < 16)
				ft_putchar('0');
			ft_put_uintmax((uint8_t)*content, 16);
			ft_putchar(' ');
		}
		if ((++i % 16) == 0 && i < sec_size)
			ft_putchar('\n');
	}
	ft_putchar('\n');
}
