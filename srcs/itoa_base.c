/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   itoa_base.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 13:36:44 by maboye            #+#    #+#             */
/*   Updated: 2019/08/28 14:17:09 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		recursion(intmax_t nb, int b, char *str, int *i)
{
	char const	base[] = "0123456789ABCDEF";

	if (nb <= -b || b <= nb)
		recursion(nb / b, b, str, i);
	str[(*i)++] = base[pf_abs(nb % b)];
}

char			*ft_itoa_base(t_printf *data, intmax_t nb, int base)
{
	char	*str;
	int		i;

	if (base < 2 || 36 < base)
		return (NULL);
	if (!nb)
	{
		if (data->flags & HASH)
			data->flags -= HASH;
		if (data->p_token && data->precision < 1)
			str = pf_strdup("");
		else
			str = pf_strdup("0");
		return (str);
	}
	if (!(str = (char *)pf_memalloc(sizeof(char) * 32)))
		return (NULL);
	i = 0;
	if (nb < 0)
		data->neg = 1;
	recursion(nb, base, str, &i);
	return (str);
}

static void		urecursion(uintmax_t nb, unsigned int b, char *str, int *i)
{
	char const	base[] = "0123456789ABCDEF";

	if (b <= nb)
		urecursion(nb / b, b, str, i);
	str[(*i)++] = base[nb % b];
}

char			*ft_uitoa_base(t_printf *data, uintmax_t nb, int base)
{
	char	*str;
	int		i;

	if (base < 2 || 36 < base)
		return (NULL);
	if (!nb)
	{
		if (data->flags & HASH)
			data->flags -= HASH;
		if (data->p_token && data->precision < 1)
			str = pf_strdup("");
		else
			str = pf_strdup("0");
		return (str);
	}
	if (!(str = (char *)pf_memalloc(sizeof(char) * 32)))
		return (NULL);
	i = 0;
	urecursion(nb, (unsigned int)base, str, &i);
	return (str);
}
