/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 14:51:38 by maboye            #+#    #+#             */
/*   Updated: 2019/08/21 18:53:44 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

void                pf_handle_width(t_printf *data)
{
    char    c;
    int     width;

    c = (data->flags & ZERO ? '0' : ' ');
    width = data->width;
    while (width-- > 1)
        pf_buffer(data, c);
}

void                pf_handle_precision(t_printf *data)
{
    (void)data;
}

void                pf_handle_flag(t_printf *data)
{
    if ((data->flags & SPC) && data->width < 1)
        pf_buffer(data, ' ');
    if (data->flags & HASH)
    {
        if (pf_strchr("xXo", data->conversion))
        {
            pf_buffer(data, 'O');
            if (data->conversion != 'o')
                pf_buffer(data, data->conversion == 'x' ? 'x' : 'X');
        }
    }
}

void            pf_handler(t_printf *data)
{
    pf_get_type(data);
    if (data->width <= data->len)
        data->width = 0;
    if ((data->precision <= data->len) && data->conversion != 's')
        data->precision = 0;
    pf_handle_flag(data);
    if (!(data->flags & LESS))
        pf_handle_width(data);
    // pf_handle_precision(data);
    pf_bufferstr(data, data->str);
    if (data->flags & LESS)
        pf_handle_width(data);
}
