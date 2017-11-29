/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/07 14:54:12 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 19:02:29 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NM_H
# define NM_H

# include "nm_otool_utils.h"

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
char				get_sym_type(uint8_t type, uint8_t nsec, uint64_t value,
					t_sec_location *sections);

int					init_env_struct(t_nm *env);
void				update_env_struct(t_nm *env, char *arg);
void				copy_env_struct(t_nm *src, t_nm *dst);
void				init_syminfos_struct(t_syminfos *syminfos);
void				init_sections_struct(t_sec_location *sections);

int					check_stringtab_validity_32(t_nm *env,
					struct nlist *array, void *stringtab, int nb_elem);
int					check_stringtab_validity_64(t_nm *env,
					struct nlist_64 *array, void *stringtab, int nb_elem);

void				print_32(t_nm *env, t_syminfos *syminfos,
					t_sec_location *sections);
void				print_64(t_nm *env, t_syminfos *syminfos,
					t_sec_location *sections);

#endif
