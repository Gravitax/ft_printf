/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:51:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:35:25 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				ft_printf(const char *format, ...)
{
	t_printf	*data;
	int			result;

	if (B_SIZE < 500)
		exit(EXIT_FAILURE);
	if (!(data = (t_printf *)pf_memalloc(sizeof(data))))
		return (-1);
	va_start(data->list, format);
	pf_parser(format, data);
	va_end(data->list);
	pf_print_buffer(data, data->i);
	result = data->count;
	free((void *)data);
	data = NULL;
	return (result);
}
