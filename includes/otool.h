/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   otool.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/23 14:45:58 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/30 14:49:00 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OTOOL_H
# define OTOOL_H

# include "nm_otool_utils.h"

typedef struct		s_otool
{
	t_executable	exec;
	char			*file_name;
	void			*file_start;
	void			*file_end;
	int				opt_data;
	int				printed;
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

void				init_env_struct(t_otool *env);
void				update_env_struct(t_otool *env, char *arg);
void				copy_env_struct(t_otool *env, t_otool *env_cpy);

int					set_section_32_endianness(t_otool *env,
					struct section *sec);
int					set_section_64_endianness(t_otool *env,
					struct section_64 *sec);
int					check_load_command_overflow(t_otool *env,
					struct load_command *lc, uint32_t ncmds);

int					is_sought_section(char *sec_name, char *seg_name,
					int option_data);
void				print_section_32(t_otool *env, struct section *sec);
void				print_section_64(t_otool *env, struct section_64 *sec);

#endif
