/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 15:03:48 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/23 16:34:20 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	add_opt(t_nm *env, char *arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		if (arg[i] == 'p' && !env->opts->p)
			env->opts->p = 1;
		else if (arg[i] == 'r' && !env->opts->r)
			env->opts->r = 1;
		else if (arg[i] == 'u' && !env->opts->u)
			env->opts->u = 1;
		else if (arg[i] == 'U' && !env->opts->U)
			env->opts->U = 1;
		else if (arg[i] == 'j' && !env->opts->j)
			env->opts->j = 1;
		else if (arg[i] == 'p' || arg[i] == 'r' || arg[i] == 'u'
		|| arg[i] == 'U' || arg[i] == 'j')
			return (put_error(DUP_OPT, env->exec, arg));
		else
			return (put_error(INVALID_OPT, env->exec, arg));
		i++;
	}
	return (0);
}

int			parse_args(t_nm *env, int ac, char **av)
{
	int		i;
	int		j;
	int		opts_end;

	i = 0;
	j = 0;
	opts_end = 0;
	while (++i < ac)
	{
		if (opts_end || av[i][0] != '-')
			av[j++] = av[i];
		else if (av[i][0] == '-' && av[i][1] == '-' && !av[i][2])
			opts_end = 1;
		else if (av[i][0] == '-' && add_opt(env, av[i]) == -1)
			return (-1);
	}
	if (j == 0)
		av[j++] = "a.out";
	av[j] = NULL;
	return (0);
}

int		ft_nm(t_nm *env)
{
	uint32_t magic_nb;

	magic_nb = *(uint32_t*)env->file_start;
	env->big_endian = is_big_endian(magic_nb);
	if (magic_nb == MH_MAGIC || magic_nb == MH_CIGAM)
		handle_32(env);
	else if (magic_nb == MH_MAGIC_64 || magic_nb == MH_CIGAM_64)
		handle_64(env);
	else if (magic_nb == FAT_MAGIC || magic_nb == FAT_CIGAM)
		handle_fat(env);
	else if (!(ft_strncmp((char*)env->file_start, ARMAG, (size_t)SARMAG)))
		handle_lib(env);
	else
		put_error(INVALID_FILE, env->exec, env->file_name);
	return (0);
}

int			handle_file(t_nm *env)
{
	int			fd;
	struct stat	buf;

	if ((fd = open(env->file_name, O_RDONLY)) == -1)
		return (put_error(OPEN, env->exec, env->file_name));
	if (fstat(fd, &buf) == -1)
		return (put_error(FSTAT, env->exec, env->file_name));
	if (S_ISDIR(buf.st_mode))
		return (put_error(DIRECTORY, env->exec, env->file_name));
	if ((env->file_start = mmap(0, buf.st_size, PROT_READ | PROT_WRITE,
	MAP_PRIVATE, fd, 0)) == MAP_FAILED)
		return (put_error(MAPPING, env->exec, env->file_name));
	env->file_end = env->file_start + buf.st_size - 1;
	ft_nm(env);
	if (munmap(env->file_start, buf.st_size) == -1)
		return (put_error(UNMAPPING, env->exec, env->file_name));
	if (close(fd) == -1)
		return (put_error(UNDEFINED, env->exec, env->file_name)); // error to define
	return (0);
}

int		main(int ac, char **av)
{
	int			i;
	int			ret;
	t_nm		env;

	i = 0;
	ret = EXIT_SUCCESS;
	env.exec = EXEC_NM;
	if (init_env_struct(&env) == -1)
		return (EXIT_FAILURE);
	if (parse_args(&env, ac, av) == -1)
		return (EXIT_FAILURE);
	if (av[1])
		env.multiple_arg = 1;
	while (av[i] != NULL)
	{
		env.file_name = av[i];
		if (handle_file(&env) == -1)
			ret = EXIT_FAILURE;
		i++;
	}
	return (ret);
}
