/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/29 12:53:51 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/30 19:54:56 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "otool.h"

static int	handle_all_archs(t_otool *env, t_otool *env_cpy,
struct fat_arch *arch, uint32_t nfat_arch)
{
	uint32_t	i;
	int			nb_arch_handled;

	i = 0;
	nb_arch_handled = 0;
	while (i < nfat_arch)
	{
		if (arch->cputype == CPU_TYPE_I386 || arch->cputype == CPU_TYPE_POWERPC
		|| arch->cputype == CPU_TYPE_POWERPC64 || arch->cputype == CPU_TYPE_X86)
		{
			if ((env_cpy->file_start = env->file_start + arch->offset)
			> env->file_end)
				return (put_error(MALFORMED, env->exec, env->file_start));
			env_cpy->current_arch = arch->cputype;
			env_cpy->multiple_arch = nfat_arch > 1 ? 1 : 0;
			if (ft_otool(env_cpy) == -1)
				return (-1);
			nb_arch_handled++;
		}
		arch = (struct fat_arch*)((void*)arch + sizeof(*arch));
		i++;
	}
	if (nb_arch_handled == 0)
		put_error(NO_ARCH, env->exec, env->file_name);
	return (0);
}

static void	*get_local_arch_ptr(t_otool *env, struct fat_arch *arch,
uint32_t nfat_arch)
{
	uint32_t	i;

	i = 0;
	while (i < nfat_arch)
	{
		if (arch->cputype == env->local_arch)
			return (env->file_start + arch->offset);
		arch = (struct fat_arch*)((void*)arch + sizeof(*arch));
		i++;
	}
	return (NULL);
}

static int	set_archs_endianness(t_otool *env, struct fat_arch *arch,
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
		arch = (struct fat_arch*)((void*)arch + sizeof(*arch));
		i++;
	}
	return (0);
}

int			handle_fat(t_otool *env)
{
	uint32_t			i;
	t_otool				env_cpy;
	struct fat_header	*header;
	struct fat_arch		*arch;

	i = 0;
	header = (struct fat_header*)env->file_start;
	header->nfat_arch = endianness(header->nfat_arch, env->big_endian);
	arch = (struct fat_arch*)(env->file_start + sizeof(*header));
	copy_env_struct(env, &env_cpy);
	if (set_archs_endianness(env, arch, header->nfat_arch) == -1)
		return (put_error(MALFORMED, env->exec, env->file_name));
	if ((env_cpy.file_start = get_local_arch_ptr(env, arch, header->nfat_arch)))
		return (ft_otool(&env_cpy));
	return (handle_all_archs(env, &env_cpy, arch, header->nfat_arch));
}
