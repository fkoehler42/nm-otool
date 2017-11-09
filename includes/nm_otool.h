/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/09 16:37:56 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_H
# define NM_OTOOL_H

# define debug ft_printf("%s, %d\n", __FILE__, __LINE__);

#include "../libft/includes/libft.h"
#include "../libft/includes/ft_printf.h"
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
	DIRECTORY,
	FSTAT,
	MALFORMED,
	MAPPING,
	OPEN,
	UNMAPPING,
	UNDEFINED
}					t_error_flag;

typedef struct		s_nm_otool
{
	t_executable	exec;
	char			*file_name;
	void			*file_start;
	void			*file_end;
}					t_nm_otool;


int					ft_nm(t_nm_otool *env);
/* void				nm_handle_32(void *file_ptr); */
int					nm_handle_64(t_nm_otool *env);

int					open_file(t_nm_otool *env);

void				ascii_sort_64(void *stringtable, struct nlist_64 *array,
					int nb_elem);

void				init_env_struct(t_nm_otool *env);
/* t_nm_otool			*get_env_struct(t_nm_otool *env); */

int					put_error(t_error_flag flag, t_executable exec, char *arg);

#endif
