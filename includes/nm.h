/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/13 19:55:28 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

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
	MALLOC,
	MAPPING,
	OPEN,
	UNMAPPING,
	UNDEFINED
}					t_error_flag;

typedef struct		s_sec_location
{
	uint32_t		bss;
	uint32_t		data;
	uint32_t		text;
	uint32_t		sec_index;
}					t_sec_location;

typedef struct		s_nm
{
	t_executable	exec;
	char			*file_name;
	void			*file_start;
	void			*file_end;
}					t_nm;


int					ft_nm(t_nm *env);
/* void				handle_32(void *file_ptr); */
int					handle_64(t_nm *env);

int					open_file(t_nm *env);

char				get_sym_type(uint8_t type, uint8_t nsec, uint64_t value,
					t_sec_location *sections);
void				ascii_sort_64(struct nlist_64 *array, void *stringtable,
					int nb_elem);

void				init_env_struct(t_nm *env);
void				init_sections_struct(t_sec_location *sections);
/* t_symtab			**create_symt_array(int nsyms, t_executable exec); */
/* t_nm			*get_env_struct(t_nm *env); */

void				print_64(struct nlist_64 *symtab, void *stringtab,
					t_sec_location *sections, uint32_t nsyms);

int					put_error(t_error_flag flag, t_executable exec, char *arg);

#endif
