/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:45:58 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/29 13:20:44 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

#include "nm_otool_utils.h"

typedef struct		s_otool
{
	t_executable	exec;
	char			*file_name;
	void			*file_start;
	void			*file_end;
	t_opts			*opts;
	cpu_type_t		local_arch;
	cpu_type_t		current_arch;
	int				multiple_arch;
	int				big_endian;
}					t_otool;

int					ft_otool(t_otool *env);
int					handle_32(t_otool *env);
int					handle_64(t_otool *env);
int					handle_fat(t_otool *env);
int					handle_lib(t_otool *env);

int					init_env_struct(t_otool *env);
void				copy_env_struct(t_otool *env, t_otool *env_cpy);

void				print_infos(char *file_name, cpu_type_t arch,
					int multiple_arch);
void				print_section_32(char *sec_name, uint32_t sec_addr,
					uint32_t sec_size, uint8_t *content);
void				print_section_64(char *sec_name, uint64_t sec_addr,
					uint64_t sec_size, uint8_t *content);

#endif
