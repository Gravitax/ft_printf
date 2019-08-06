/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:50:48 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 17:17:30 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				pf_atoi(const char *str)
{
	int			x;
	int			signe;
	long long	entier;

	x = 0;
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

int				pf_get_base(char c)
{
	if (c == 'X' || c == 'x' || c == 'p')
		return (16);
	else if (c == 'o')
		return (8);
	else
		return (10);
}

char			*pf_itoa(int n)
{
	char	ret[11];
	char	*r;
	int		neg;
	int		i;
	int		j;

	j = 0;
	i = 0;
	neg = n < 0 ? -1 : 1;
	while (neg * n > 9 || neg * n < 0)
	{
		ret[i++] = '0' + neg * (n % 10);
		n = n / 10;
	}
	ret[i++] = '0' + neg * n;
	if (neg < 0)
		ret[i++] = '-';
	if (!(r = (char *)malloc(sizeof(char) * (i + 1))))
		return ((void *)0);
	while (i--)
		r[i] = ret[j++];
	return (r);
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
