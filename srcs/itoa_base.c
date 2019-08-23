/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:36:44 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:37:30 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		recursion(intmax_t nb, int b, char *str, int *i)
{
	char const	base[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (nb <= -b || b <= nb)
		recursion(nb / b, b, str, i);
	str[(*i)++] = base[pf_abs(nb % b)];
}

char			*ft_itoa_base(intmax_t nb, int base)
{
	char	*str;
	int		i;

	if (base < 2 || 36 < base)
		return (NULL);
	if (!(str = (char *)pf_memalloc(sizeof(char) * 32)))
		return (NULL);
	i = 0;
	if (nb < 0)
		str[i++] = '-';
	recursion(nb, base, str, &i);
	return (str);
}

static void		urecursion(uintmax_t nb, int b, char *str, int *i)
{
	char const	base[] = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

	if (nb <= (uintmax_t)-b || (uintmax_t)b <= nb)
		urecursion(nb / b, b, str, i);
	str[(*i)++] = base[nb % b];
}

char			*ft_uitoa_base(uintmax_t nb, int base)
{
	char	*str;
	int		i;

	if (base < 2 || 36 < base)
		return (NULL);
	if (!(str = (char *)pf_memalloc(sizeof(char) * 32)))
		return (NULL);
	i = 0;
	urecursion(nb, base, str, &i);
	return (str);
}
