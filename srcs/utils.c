/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:47:26 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:25:06 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

intmax_t		pf_abs(intmax_t nb)
{
	return (nb < 0 ? -nb : nb);
}

int				pf_isdigit(int c)
{
	return (c >= '0' && c <= '9');
}

int				pf_isspace(int c)
{
	return (c == ' ' || c == '\t' || c == '\n');
}

void			pf_strtolower(char *str)
{
	while (str && *str++)
	{
		if (*str >= 'A' && *str <= 'Z')
			*str += 32;
	}
}
