/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:50:48 by maboye            #+#    #+#             */
/*   Updated: 2019/08/27 17:18:26 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			*pf_memalloc(size_t size)
{
	void	*ptr;

	if (!(ptr = malloc(size)))
		return (NULL);
	while (size--)
		((char *)ptr)[size] = (unsigned char)0;
	return (ptr);
}

void			*pf_memset(void *ptr, int c, size_t len)
{
	while (len--)
		((char *)ptr)[len] = (unsigned char)c;
	return (ptr);
}

char			*pf_strchr(const char *ptr, int c)
{
	while (ptr && *ptr)
	{
		if (*ptr == (char)c)
			return ((char *)ptr);
		++ptr;
	}
	return (NULL);
}

char			*pf_strdup(const char *src)
{
	char	*s;
	char	*ret;

	if (!src)
		return (NULL);
	if (!(ret = (char *)pf_memalloc(sizeof(char) * (pf_strlen(src) + 1))))
		return (NULL);
	s = ret;
	while (src && *src)
	{
		*s = *src;
		++s;
		++src;
	}
	return (ret);
}

size_t			pf_strlen(const char *str)
{
	char	*p;

	if (!str)
		return (0);
	p = (char *)str;
	while (p && *p)
		++p;
	return (p - str);
}
