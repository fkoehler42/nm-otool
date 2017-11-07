/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_put_intmax.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/10/02 14:15:59 by fkoehler          #+#    #+#             */
/*   Updated: 2017/10/02 16:02:36 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <libft.h>

void	ft_put_intmax(intmax_t n, int base)
{
	if (n < 0)
	{
		ft_putchar('-');
		ft_put_uintmax(-n, base);
	}
	else
	{
		if (n >= base)
			ft_put_intmax(n / base, base);
		if (n % base > 9)
			ft_putchar(n % base + 87);
		else
			ft_putchar(n % base + 48);
	}
}

void	ft_put_uintmax(uintmax_t n, int base)
{
	if (n >= (unsigned int)base)
		ft_put_uintmax(n / base, base);
	if (n % base > 9)
		ft_putchar(n % base + 87);
	else
		ft_putchar(n % base + 48);
}

void	ft_put_intmax_fd(intmax_t n, int base, int fd)
{
	if (n < 0)
	{
		ft_putchar_fd('-', fd);
		ft_put_uintmax_fd(-n, base, fd);
	}
	else
	{
		if (n >= base)
			ft_put_intmax_fd(n / base, base, fd);
		if (n % base > 9)
			ft_putchar_fd(n % base + 87, fd);
		else
			ft_putchar_fd(n % base + 48, fd);
	}
}

void	ft_put_uintmax_fd(uintmax_t n, int base, int fd)
{
	if (n >= (unsigned int)base)
		ft_put_uintmax_fd(n / base, base, fd);
	if (n % base > 9)
		ft_putchar_fd(n % base + 87, fd);
	else
		ft_putchar_fd(n % base + 48, fd);
}
