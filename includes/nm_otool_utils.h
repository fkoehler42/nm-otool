/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_otool_utils.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 16:03:02 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 19:18:05 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_OTOOL_UTILS_H
# define NM_OTOOL_UTILS_H

# include "../libft/includes/libft.h"
# include "../libft/includes/ft_printf.h"
# include <fcntl.h>
# include <sys/stat.h>
# include <sys/mman.h>
# include <mach-o/loader.h>
# include <mach-o/nlist.h>
# include <mach-o/fat.h>
# include <mach-o/ranlib.h>
# include <mach-o/arch.h>
# include <ar.h>

typedef enum		e_executable
{
	EXEC_NM,
	EXEC_OTOOL,
	NONE
}					t_executable;

typedef enum		e_error_flag
{
	CLOSE,
	DIRECTORY,
	DUP_OPT,
	FSTAT,
	INVALID_FILE,
	INVALID_OPT,
	MALFORMED,
	MALLOC,
	MAPPING,
	NO_ARCH,
	NO_ARG,
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

typedef struct		s_syminfos
{
	void			*stringtab;
	struct nlist	*symtab_32;
	struct nlist_64	*symtab_64;
	uint32_t		nsyms;
}					t_syminfos;

/*
** ft_nm available opts :
**
** -p : don't sort symbols (table order)
** -r : sort in reverse order
** -u : display only undefined symbols (name only)
** -U : don't display undefined symbols
** -j : display the symbol names only (no value or type)
**
** ft_otool available opts :
**
** by default, the behaviour is the -t option one (display text section)
** -d : display the data section
*/

typedef struct		s_opts
{
	int				p;
	int				r;
	int				u;
	int				uu;
	int				j;
}					t_opts;

int					is_big_endian(uint32_t magic_nb);
uint64_t			endianness(uint64_t value, int is_big_endian);
void				set_symtab_endianness_32(struct nlist *symtab,
					uint32_t nsyms, int is_big_endian);
void				set_symtab_endianness_64(struct nlist_64 *symtab,
					uint32_t nsyms, int is_big_endian);

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

int					put_error(t_error_flag flag, t_executable exec, char *arg);

#endif
