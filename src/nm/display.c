/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:10:45 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/22 18:19:18 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	print_infos(char *file_name, cpu_type_t arch, int multiple_arg,
int multiple_arch)
{
	char	*arch_name;

	arch_name = NULL;
	if (multiple_arch && arch)
	{
		if (arch == CPU_TYPE_I386)
			arch_name = "i386";
		else if (arch == CPU_TYPE_X86)
			arch_name = "x86";
		else if (arch == CPU_TYPE_POWERPC)
			arch_name = "ppc";
		else if (arch == CPU_TYPE_POWERPC64)
			arch_name = "ppc64";
		ft_printf("\n%s (for architecture %s):\n", file_name, arch_name);
	}
	else if (multiple_arg && arch != -1)
		ft_printf("\n%s:\n", file_name);
}

static void	print_sym_32(uint32_t value, char type, char *str)
{
	if (!ft_strcmp(str, "radr://5614542") || type == '-')
		return ;
	if (!value && (type == 'u' || type == 'U'))
		ft_printf("%8c %c %s\n", ' ', type, str);
	else
		ft_printf("%08lx %c %s\n", value, type, str);
}

static void	print_sym_64(uint64_t value, char type, char *str)
{
	if (!ft_strcmp(str, "radr://5614542") || type == '-')
		return ;
	if (!value && (type == 'u' || type == 'U'))
		ft_printf("%16c %c %s\n", ' ', type, str);
	else
		ft_printf("%016llx %c %s\n", value, type, str);
}

void		print_32(t_nm *env, t_syminfos *syminfos, t_sec_location *sections)
{
	uint32_t	i;
	char		sym_type;

	i = 0;
	if (check_stringtab_validity_32(env, syminfos->symtab_32,
	syminfos->stringtab, syminfos->nsyms) == -1)
		return;
	ascii_sort_32(syminfos->symtab_32, syminfos->stringtab,
	syminfos->nsyms);
	print_infos(env->file_name, env->current_arch, env->multiple_arg,
	env->multiple_arch);
	while (i < syminfos->nsyms)
	{
		sym_type = get_sym_type(syminfos->symtab_32[i].n_type,
		syminfos->symtab_32[i].n_sect,
		(uint64_t)syminfos->symtab_32[i].n_value, sections);
		print_sym_32(syminfos->symtab_32[i].n_value, sym_type,
		(char*)(syminfos->stringtab + syminfos->symtab_32[i].n_un.n_strx));
		i++;
	}
}

void		print_64(t_nm *env, t_syminfos *syminfos, t_sec_location *sections)
{
	uint32_t	i;
	char		sym_type;

	i = 0;
	if (check_stringtab_validity_64(env, syminfos->symtab_64,
	syminfos->stringtab, syminfos->nsyms) == -1)
		return;
	ascii_sort_64(syminfos->symtab_64, syminfos->stringtab,
	syminfos->nsyms);
	print_infos(env->file_name, env->current_arch, env->multiple_arg,
	env->multiple_arch);
	while (i < syminfos->nsyms)
	{
		sym_type = get_sym_type(syminfos->symtab_64[i].n_type,
		syminfos->symtab_64[i].n_sect,
		syminfos->symtab_64[i].n_value, sections);
		print_sym_64(syminfos->symtab_64[i].n_value, sym_type,
		(char*)(syminfos->stringtab + syminfos->symtab_64[i].n_un.n_strx));
		i++;
	}
}
