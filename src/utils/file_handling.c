/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:09:14 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 12:09:17 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		open_file(t_executable exec, char *file)
{
	int			fd;
	void		*ptr;
	struct stat	buf;

	if ((fd = open(file, O_RDONLY)) == -1)
		return (put_error(OPEN, exec, file));
	if (fstat(fd, &buf) == -1)
		return (put_error(FSTAT, exec, file));
	if (S_ISDIR(buf.st_mode))
		return (put_error(DIRECTORY, exec, file));
	if ((ptr = mmap(0, buf.st_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0))
	== MAP_FAILED)
		return (put_error(MAPPING, exec, file));
	if (exec == EXEC_NM)
		ft_nm(ptr);
	/* else if (exec == EXEC_OTOOL) */
		/* ft_otool(ptr); */
	if (munmap(ptr, buf.st_size) == -1)
		return (put_error(UNMAPPING, exec, file));
	return (0);
}
