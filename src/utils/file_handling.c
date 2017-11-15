/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:09:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 15:26:57 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

int			is_big_endian(uint32_t magic_nb)
{
	return (magic_nb == MH_CIGAM || magic_nb == MH_CIGAM_64
	|| magic_nb == FAT_CIGAM);
}

uint32_t	swap_bytes_uint32(uint32_t value)
{
	return (((value & 0xFF) << 24) | (((value >> 8) & 0xFF) << 16) |
	(((value >> 16) & 0xFF) << 8) | ((value >> 24) & 0xFF));
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
	if (env->exec == EXEC_NM)
		ft_nm(env);
	/* else if (exec == EXEC_OTOOL) */
		/* ft_otool(ptr); */
	if (munmap(env->file_start, buf.st_size) == -1)
		return (put_error(UNMAPPING, env->exec, env->file_name));
	if (close(fd) == -1)
		return (put_error(UNDEFINED, env->exec, env->file_name)); // error to define
	return (0);
}
