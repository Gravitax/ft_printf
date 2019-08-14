/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 17:08:55 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 17:16:40 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				pf_is_conversion(const char c)
{
	return (pf_strchr("dDioOuUxXeEfFgGaAcCsSpn%", c) != NULL);
}

int				pf_is_modifier(const char c)
{
	return (pf_strchr("hljz", c) != NULL);
}

int				pf_is_flag(const char c)
{
	return (pf_strchr("#0-+ ", c) != NULL);
}

int				pf_is_precision(const char c)
{
	return (pf_strchr("$*.", c) != NULL);
}

int				pf_is_valid(const char c)
{
	return (pf_is_conversion(c) || pf_is_modifier(c) || pf_is_flag(c) ||
			pf_isdigit(c) || pf_is_precision(c));
}
