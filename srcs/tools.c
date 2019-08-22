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
	return (NULL);
}

size_t			pf_strlen(const char *s, size_t max)
{
	size_t i;

	if (!s)
		return (0);
	i = 0;
	if (max)
		while (s[i] && i < max)
			i++;
	else
		while (s[i])
			i++;
	return (i);
}
