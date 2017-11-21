/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:45:22 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/21 12:55:30 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	*get_local_arch_ptr(t_nm *env, struct fat_arch *arch,
uint32_t nfat_arch)
{
	uint32_t	i;

	i = 0;
	while (i < nfat_arch)
	{
		if (arch->cputype == env->local_arch)
			return (env->file_start + arch->offset);
		arch = (struct fat_arch*)(void*)arch + sizeof(*arch);
		i++;
	}
	return (NULL);
}

static int	set_archs_endianness(t_nm *env, struct fat_arch *arch,
uint32_t nfat_arch)
{
	uint32_t	i;

	i = 0;
	while (i < nfat_arch)
	{
		if ((void*)arch > env->file_end)
			return (-1);
		arch->offset = endianness(arch->offset, env->big_endian);
		arch->cputype = endianness(arch->cputype, env->big_endian);
		arch = (struct fat_arch*)(void*)arch + sizeof(*arch);
		i++;
	}
	return (0);
}

int			handle_fat(t_nm *env)
{
	uint32_t			i;
	t_nm				env_cpy;
	struct fat_header	*header;
	struct fat_arch		*arch;

	i = 0;
	header = (struct fat_header*)env->file_start;
	header->nfat_arch = endianness(header->nfat_arch, env->big_endian);
	arch = (struct fat_arch*)(env->file_start + sizeof(*header));
	copy_env_struct(env, &env_cpy);
	if (set_archs_endianness(env, arch, header->nfat_arch) == -1)
		return (put_error(MALFORMED, env->exec, env->file_name));
	if (env->local_arch &&
	(env_cpy.file_start = get_local_arch_ptr(env, arch, header->nfat_arch)))
		return (ft_nm(&env_cpy));
	return (handle_all_archs(env, &env_cpy, arch, nfat_arch));
}
