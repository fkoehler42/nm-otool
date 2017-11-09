/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:03:48 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 16:43:52 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		ft_nm(t_nm_otool *env)
{
	uint32_t magic_nb;

	magic_nb = *(uint32_t*)env->file_start;
	if (magic_nb == MH_MAGIC)
		return 0;
		/* nm_handle_32(file_ptr); */
	else if (magic_nb == MH_MAGIC_64)
		nm_handle_64(env);
	return (0);
}

int		main(int ac, char **av)
{
	int			i;
	int			ret;
	t_nm_otool	env;

	i = 0;
	ret = EXIT_SUCCESS;
	env.exec = EXEC_NM;
	init_env_struct(&env);
	if (ac == 1)
	{
		env.file_name = "a.out";
		ret = open_file(&env);
	}
	else
	{
		while (++i < ac)
		{
			env.file_name = av[i];
			if (open_file(&env) == -1)
				ret = EXIT_FAILURE;
		}
	}
	return (ret);
}
