/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:50:48 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 17:51:42 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				pf_atoi(const char *str, int x)
{
	int			signe;
	long long	entier;

	entier = 0;
	while (pf_isspace(str[x]))
		x++;
	signe = (str[x] == '-') ? -1 : 1;
	(str[x] == '-' || str[x] == '+') ? x++ : 0;
	while (pf_isdigit(str[x]))
	{
		if (entier * signe > 2147483647)
			return (-1);
		if (entier * signe < -2147483648)
			return (0);
		entier = entier * 10 + (str[x++] - '0');
	}
	return ((int)entier * signe);
}

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
	//	if ((char)c == '\0')
	//		return ((char *)s);
	return (NULL);
}

// char			*pf_strdup(const char *src)
// {
// 	char	*copy;
// 	char	*tmp;

// 	if (!(copy = (char *)malloc(sizeof(char) * (pf_strlen(src, 0) + 1))))
// 		return (NULL);
// 	tmp = copy;
// 	while ((*tmp++ = *src++) != 0)
// 		;
// 	return (copy);
// }

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
