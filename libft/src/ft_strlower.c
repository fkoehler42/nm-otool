/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 19:36:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 19:37:00 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strlower(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		str[i] = (char)ft_tolower((int)str[i]);
		i++;
	}
	return (str);
}
