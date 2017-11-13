/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sym_type.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fkoehler <fkoehler@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/13 19:42:28 by fkoehler          #+#    #+#             */
/*   Updated: 2017/11/13 20:03:21 by fkoehler         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "nm.h"

static char	nsec_type(uint8_t nsec, t_sec_location *sections)
{
	if (nsec == sections->text)
		return ('T');
	if (nsec == sections->data)
		return ('D');
	if (nsec == sections->bss)
		return ('B');
	return ('S');
}

char		get_sym_type(uint8_t type, uint8_t nsec, uint64_t value,
		t_sec_location *sections)
{
	char	c;

	c = (char)type;
	if (c & N_STAB)
		return ('-');
	c = c & N_TYPE;
	if (c == N_UNDF && value != 0)
		c = 'C';
	else if ((c == N_UNDF && value == 0) || c == N_PBUD)
		c = 'U';
	else if (c == N_ABS)
		c = 'A';
	else if (c == N_SECT)
		c = nsec_type(nsec, sections);
	else
		c = (c == N_INDR ? 'I' : '?');
	if (!(type & N_EXT))
		c = ft_tolower(c);
	return (c);
}
