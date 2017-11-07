/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:03:48 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/07 17:18:25 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		main(int ac, char **av)
{
	int	i;
	int	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (ac == 1)
		ret = parse_arg("a.out");
	else
	{
		while (++i < ac)
		{
			if (parse_arg(av[i]) == 1)
				ret = EXIT_FAILURE;
		}
	}
	return (ret);
}
