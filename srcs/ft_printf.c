/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:51:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 18:38:07 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_printf(const char *format, ...)
{
	va_list	list;
	int		result;

	if (!pf_strlen(format, 0))
		return (0);
	va_start(list, format);
	result = pf_parser(format, list);
	va_end(list);
	return (result);
}
