/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:50:48 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 22:37:50 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

intmax_t		pf_intlen(intmax_t nb)
{
	int		i;

	i = 0;
	nb = nb < 0 ? -nb : nb;
	while (nb >= 10)
	{
		++i;
		nb /= 10;
	}
	return (i + 1);
}

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
		ptr++;
	}
	return (NULL);
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
