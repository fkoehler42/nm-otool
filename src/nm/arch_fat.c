/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arch_fat.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 12:45:22 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/15 17:47:06 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static int	parse_arch(t_nm *env, t_nm *env_cpy, struct fat_arch *arch)
{
	if (env->big_endian)
		arch->offset = swap_bytes_uint32(arch->offset);
	if (swap_bytes_uint32(arch->cputype) == CPU_TYPE_X86_64)
	{
		env_cpy->file_start = env->file_start + arch->offset;
		return (ft_nm(env_cpy));
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
	if (env->big_endian)
		header->nfat_arch = swap_bytes_uint32(header->nfat_arch);
	arch = (struct fat_arch*)(env->file_start + sizeof(*header));
	copy_env_struct(env, &env_cpy);
	while (i < header->nfat_arch)
	{
		if ((void*)arch > env->file_end)
			return (put_error(MALFORMED, env->exec, env->file_name));
		if (parse_arch(env, &env_cpy, arch) == -1)
			return (-1);
		arch = (struct fat_arch*)(void*)arch + sizeof(*arch);
		i++;
	}
	return (0);
}
