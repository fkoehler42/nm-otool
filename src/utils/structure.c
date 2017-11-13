/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structure.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/09 12:35:16 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/13 18:10:54 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

void		init_env_struct(t_nm *env)
{
	env->file_name = NULL;
	env->file_start = NULL;
	env->file_end = NULL;
}

void		init_sections_struct(t_sec_location *sections)
{
	sections->bss = 0;
	sections->data = 0;
	sections->text = 0;
	sections->sec_index = 1;
}

/*
t_symtab	**create_symt_array(int nsyms, t_executable exec)
{
	int			i;
	t_symtab	**array;

	i = 0;
	if (!(array = (t_symtab**)malloc(sizeof(*array) * (nsyms + 1))))
	{
		put_error(MALLOC, exec, NULL);
		return (NULL);
	}
	while (i < nsyms)
	{
		if (!(array[i] = (t_symtab*)malloc(sizeof(**array))))
		{
			put_error(MALLOC, exec, NULL);
			return (NULL);
		}
		array[i]->value = 0;
		array[i]->str = NULL;
		i++;
	}
	array[i] = NULL;
	return (array);
}

   t_nm	*get_env_struct(t_nm *env)
   {
   static t_nm	*env_save = NULL;

   if (env != NULL)
   env_save = env;
   return (env_save);
   }
*/
