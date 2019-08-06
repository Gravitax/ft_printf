/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:47:26 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 17:17:14 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				pf_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int				pf_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

int				pf_max(int a, int b)
{
	return (a > b ? a : b);
}

void			*pf_memalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	while (size-- > 0)
		((unsigned char *)ptr)[size] = (unsigned char)0;
	return (ptr);
}

char			*pf_strchr(const char *s, int c)
{
	while (s && *s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}
