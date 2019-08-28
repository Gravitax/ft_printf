/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:03:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/28 13:21:09 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void			pf_print_buffer(t_printf *data, int len)
{
	if (data->i > 0)
		write(1, data->buf, len);
	pf_memset(data->buf, 0, B_SIZE);
	data->i = 0;
}

void			pf_bufferstr(t_printf *data, char *str)
{
	int	i;

	i = -1;
	while (str && ++i < data->len)
	{
		if (data->i > B_SIZE - 10)
			pf_print_buffer(data, B_SIZE);
		data->buf[data->i++] = str[i];
		++data->count;
	}
}

void			pf_buffer(t_printf *data, char c)
{
	if (data->i > B_SIZE - 10)
		pf_print_buffer(data, B_SIZE);
	data->buf[data->i++] = c;
	++data->count;
}
