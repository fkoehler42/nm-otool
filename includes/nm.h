/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 18:21:57 by fkoehler         ###   ########.fr       */
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
#include <mach-o/fat.h>
#include <mach-o/ranlib.h>
#include <ar.h>

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
	int				big_endian;
}					t_nm;


int					ft_nm(t_nm *env);
int					handle_32(t_nm *env);
int					handle_64(t_nm *env);
int					handle_fat(t_nm *env);
int					handle_lib(t_nm *env);

int					is_big_endian(uint32_t magic_nb);
uint32_t			swap_bytes_uint32(uint32_t value);
int					handle_file(t_nm *env);

char				get_sym_type(uint8_t type, uint8_t nsec, uint64_t value,
					t_sec_location *sections);

void				ascii_sort_32(struct nlist *array, void *stringtable,
					int nb_elem);
void				ascii_sort_64(struct nlist_64 *array, void *stringtable,
					int nb_elem);

void				init_env_struct(t_nm *env);
void				copy_env_struct(t_nm *src, t_nm *dst);
void				init_sections_struct(t_sec_location *sections);

void				print_32(struct nlist *symtab, void *stringtab,
					t_sec_location *sections, uint32_t nsyms);
void				print_64(struct nlist_64 *symtab, void *stringtab,
					t_sec_location *sections, uint32_t nsyms);

int					put_error(t_error_flag flag, t_executable exec, char *arg);

#endif
