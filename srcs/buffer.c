/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/20 18:03:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/21 13:39:35 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void		pf_print_buffer(t_printf *data, int len)
{
    if (data->i)
	    write(1, data->buf, len);
}

void        pf_bufferstr(t_printf *data, char *str)
{
    while (str && *str)
    {
        if (data->i > B_SIZE - 1)
	    {
		    pf_print_buffer(data, B_SIZE);
		    data->i = 0;
	    }
        data->buf[data->i++] = *str++;
        ++data->count;
    }
}

void		pf_buffer(t_printf *data, char c)
{
	if (data->i > B_SIZE - 1)
	{
		pf_print_buffer(data, B_SIZE);
		data->i = 0;
	}
	data->buf[data->i++] = c;
	++data->count;
}
