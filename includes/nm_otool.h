/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 14:57:33 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# define debug ft_putstr(__FILE__);ft_putstr(" --> line ");ft_putnbr(__LINE__);ft_putchar('\n');

#include "../libft/includes/libft.h"
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <mach-o/loader.h>
#include <mach-o/nlist.h>

typedef enum		e_executable
{
	EXEC_NM,
	EXEC_OTOOL,
	NONE
}					t_executable;

typedef enum		e_error_flag
{
	OPEN,
	FSTAT,
	DIRECTORY,
	MALLOC,
	MAPPING,
	UNMAPPING,
	UNDEFINED
}					t_error_flag;

typedef struct		s_nm_otool
{
	uintmax_t		file_size;
}					t_nm_otool;


int					ft_nm(void *file_ptr);
/* void				nm_handle_32(void *file_ptr); */
void				nm_handle_64(void *file_ptr);

int					open_file(t_executable exec, char *file);

void				ascii_sort_64(void *stringtable, struct nlist_64 *array,
					int nb_elem);

int					init_env_struct(t_executable exec);
t_nm_otool			*get_env_struct(t_nm_otool *env);

int					put_error(t_error_flag flag, t_executable exec, char *arg);

#endif
