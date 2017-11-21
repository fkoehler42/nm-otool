/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:13:33 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/21 14:30:11 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	put_error_2(t_error_flag flag)
{
	if (flag == NO_ARCH)
		ft_putstr_fd(": Unknown architecture(s)\n", 2);
	else if (flag == INVALID_OPT)
		ft_putstr_fd(": Invalid argument\n", 2);
	else if (flag == DUP_OPT)
		ft_putstr_fd(": Duplicate option is invalid\n", 2);
	if (flag == INVALID_OPT || flag == DUP_OPT)
		ft_putstr_fd("Usage : ft_nm [-pruUj] [file ...]\n", 2);
}

int			put_error(t_error_flag flag, t_executable exec, char *arg)
{
	if (exec == EXEC_NM)
		ft_putstr_fd("ft_nm: ", 2);
	else if (exec == EXEC_OTOOL)
		ft_putstr_fd("ft_otool: ", 2);
	if (arg != NULL)
		ft_putstr_fd(arg, 2);
	if (flag == OPEN)
		ft_putstr_fd(": No such file or directory.\n", 2);
	else if (flag == FSTAT)
		ft_putstr_fd(": Permission denied.\n", 2);
	else if (flag == DIRECTORY)
		ft_putstr_fd(": Is a directory.\n", 2);
	else if (flag == MALFORMED)
		ft_putstr_fd(": The file is malformed.\n", 2);
	else if (flag == MALLOC)
		ft_putstr_fd(": Memory allocation error.\n", 2);
	else if (flag == MAPPING)
		ft_putstr_fd(": Unable to map the file into memory.\n", 2);
	else if (flag == UNMAPPING)
		ft_putstr_fd(": Unable to release the file from memory.\n", 2);
	else
		put_error_2(flag);
	return (-1);
}
