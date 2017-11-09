/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:03:48 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 14:03:00 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		ft_nm(void *file_ptr)
{
	uint32_t magic_nb;

	magic_nb = *(uint32_t*)file_ptr;
	if (magic_nb == MH_MAGIC)
		return 0;
		/* nm_handle_32(file_ptr); */
	else if (magic_nb == MH_MAGIC_64)
		nm_handle_64(file_ptr);
	return (0);
}

int		main(int ac, char **av)
{
	int	i;
	int	ret;

	i = 0;
	ret = EXIT_SUCCESS;
	if (init_env_struct(EXEC_NM) == 1)
		return (EXIT_FAILURE);
	if (ac == 1)
		ret = open_file(EXEC_NM, "a.out");
	else
	{
		while (++i < ac)
		{
			if (open_file(EXEC_NM, av[i]) == 1)
				ret = EXIT_FAILURE;
		}
	}
	return (ret);
}
