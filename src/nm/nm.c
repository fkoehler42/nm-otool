/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:03:48 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 18:22:01 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int		ft_nm(t_nm *env)
{
	uint32_t magic_nb;

	magic_nb = *(uint32_t*)env->file_start;
	env->big_endian = is_big_endian(magic_nb);
	if (magic_nb == MH_MAGIC)
		handle_32(env);
	else if (magic_nb == MH_MAGIC_64)
		handle_64(env);
	else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
		handle_fat(env);
	else if (!(ft_strncmp((char*)env->file_start, ARMAG, (size_t)SARMAG)))
		handle_lib(env);
	return (0);
}

int		main(int ac, char **av)
{
	int			i;
	int			ret;
	t_nm	env;

	i = 0;
	ret = EXIT_SUCCESS;
	env.exec = EXEC_NM;
	init_env_struct(&env);
	if (ac == 1)
	{
		env.file_name = "a.out";
		ret = handle_file(&env);
	}
	else
	{
		while (++i < ac)
		{
			env.file_name = av[i];
			if (handle_file(&env) == -1)
				ret = EXIT_FAILURE;
		}
	}
	return (ret);
}
