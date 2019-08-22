/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:47:26 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 17:51:51 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

intmax_t		pf_abs(intmax_t nb)
{
	return (nb < 0 ? -nb : nb);
}

// int				pf_get_base(char c)
// {
// 	if (c == 'X' || c == 'x' || c == 'p')
// 		return (16);
// 	else if (c == 'o')
// 		return (8);
// 	else
// 		return (10);
// }

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
