/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ar_lib.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/15 18:19:47 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/22 15:39:08 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static void	browse_lib_ar(t_nm *env, uint32_t *ar_offset_array,
uint32_t array_len)
{
	uint32_t		i;
	uint32_t		ar_header_offset;
	char			*ar_name;
	struct ar_hdr	*ar_header;
	t_nm			env_cpy;

	i = 0;
	copy_env_struct(env, &env_cpy);
	env_cpy.current_arch = -1;
	while (i < array_len)
	{
		ar_header = (struct ar_hdr*)(env->file_start + ar_offset_array[i]);
		ar_name = ft_strstr(ar_header->ar_name, ARFMAG) + ft_strlen(ARFMAG);
		ar_header_offset = ft_atoi(ft_strchr(ar_header->ar_name, '/') + 1);
		env_cpy.file_start = (void*)ar_header
		+ sizeof(*ar_header) + ar_header_offset;
		ft_printf("\n%s(%s):\n", env->file_name, ar_name);
		ft_nm(&env_cpy);
		i++;
	}
}

void	handle_lib_ar(t_nm *env, struct ranlib *libtab, uint32_t libsize)
{
	uint32_t	i;
	uint32_t	j;
	uint32_t	ar_offset_array[libsize];
	uint32_t	array_len;

	i = 0;
	array_len = 0;
	while (i < libsize)
	{
		j = 0;
		while (j < array_len)
		{
			if (libtab[i].ran_off == ar_offset_array[j])
				break;
			j++;
		}
		if (j == array_len)
		{
			ar_offset_array[j] = libtab[i].ran_off;
			array_len++;
		}
		i++;
	}
	asc_sort_offset_array(ar_offset_array, array_len);
	browse_lib_ar(env, ar_offset_array, array_len);
}

int		handle_lib(t_nm *env)
{
	uint32_t		offset;
	uint32_t		libsize;
	void			*offset_addr;
	struct ranlib	*libtab;

	offset = ft_atoi(ft_strchr((char*)(env->file_start + SARMAG), '/') + 1);
	offset_addr = env->file_start + sizeof(struct ar_hdr) + SARMAG + offset;
	libtab = (struct ranlib*)(offset_addr + sizeof(uint32_t));
	libsize = (*((int*)offset_addr)) / sizeof(struct ranlib);
	if (offset_addr > env->file_end || (void*)libtab > env->file_end)
		return (put_error(MALFORMED, env->exec, env->file_name));
	handle_lib_ar(env, libtab, libsize);
	return (0);
}
