/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/22 19:13:52 by fkoehler         ###   ########.fr       */
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
#include <mach-o/arch.h>
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
	DUP_OPT,
	FSTAT,
	INVALID_FILE,
	INVALID_OPT,
	MALFORMED,
	MALLOC,
	MAPPING,
	NO_ARCH,
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

typedef struct			s_syminfos
{
	void				*stringtab;
	struct nlist		*symtab_32;
	struct nlist_64		*symtab_64;
	uint32_t			nsyms;
}						t_syminfos;

/*
 * ft_nm available opts :
 * -p : don't sort symbols (table order)
 * -r : sort in reverse order
 * -u : display only undefined symbols (name only)
 * -U : don't display undefined symbols
 * -j : display the symbol names only (no value or type)
*/

typedef struct		s_opts
{
	int				p;
	int				r;
	int				u;
	int				U;
	int				j;
}					t_opts;

typedef struct		s_nm
{
	t_executable	exec;
	char			*file_name;
	void			*file_start;
	void			*file_end;
	t_opts			*opts;
	cpu_type_t		local_arch;
	cpu_type_t		current_arch;
	int				multiple_arg;
	int				multiple_arch;
	int				big_endian;
}					t_nm;


int					ft_nm(t_nm *env);
int					parse_args(t_nm *env, int ac, char **av);
int					handle_file(t_nm *env);
int					handle_32(t_nm *env);
int					handle_64(t_nm *env);
int					handle_fat(t_nm *env);
int					handle_lib(t_nm *env);

int					is_big_endian(uint32_t magic_nb);
uint64_t			endianness(uint64_t value, int is_big_endian);
void				set_symtab_endianness_32(struct nlist *symtab,
					uint32_t nsyms, int is_big_endian);
void				set_symtab_endianness_64(struct nlist_64 *symtab,
					uint32_t nsyms, int is_big_endian);

char				get_sym_type(uint8_t type, uint8_t nsec, uint64_t value,
					t_sec_location *sections);

void				asc_sort_offset_array(uint32_t *array, uint32_t array_len);
void				sort_symtab(t_syminfos *syminfos, t_opts *opts);
void				ascii_sort_32(struct nlist *array, void *stringtable,
					int nb_elem);
void				rev_ascii_sort_32(struct nlist *array, void *stringtable,
					int nb_elem);
void				ascii_sort_64(struct nlist_64 *array, void *stringtable,
					int nb_elem);
void				rev_ascii_sort_64(struct nlist_64 *array, void *stringtable,
					int nb_elem);

int					init_env_struct(t_nm *env);
void				copy_env_struct(t_nm *src, t_nm *dst);
void				init_syminfos_struct(t_syminfos *syminfos);
void				init_sections_struct(t_sec_location *sections);

void				print_32(t_nm *env, t_syminfos *syminfos,
					t_sec_location *sections);
void				print_64(t_nm *env, t_syminfos *syminfos,
					t_sec_location *sections);

int					check_stringtab_validity_32(t_nm *env,
					struct nlist *array, void *stringtable, int nb_elem);
int					check_stringtab_validity_64(t_nm *env,
					struct nlist_64 *array, void *stringtable, int nb_elem);
int					put_error(t_error_flag flag, t_executable exec, char *arg);

#endif
