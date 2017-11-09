/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/08 11:13:33 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 16:34:55 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm_otool.h"

int		put_error(t_error_flag flag, t_executable exec, char *arg)
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
		ft_putstr_fd(": The file is malformed\n", 2);
	else if (flag == MAPPING)
		ft_putstr_fd(": Unable to map the file into memory.\n", 2);
	else if (flag == UNMAPPING)
		ft_putstr_fd(": Unable to release the file from memory.\n", 2);
	return (-1);
}
