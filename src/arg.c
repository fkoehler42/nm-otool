/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 16:56:50 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/07 18:13:00 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"
#include <fcntl.h>
#include <sys/stat.h>

int		parse_arg(char *arg)
{
	int			fd;
	struct stat	buf;

	if ((fd = open(arg, O_RDONLY)) == -1)
	{
		// error funct
		return (1);
	}
	if (fstat(fd, &buf) == -1)
	{
		// error funct
		return (-1);
	}
	return (0);
}
