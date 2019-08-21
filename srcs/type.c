/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   type.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/21 14:57:34 by maboye            #+#    #+#             */
/*   Updated: 2019/08/21 18:36:42 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static char         *pf_unsigned_type(t_printf *data)
{
    uintmax_t   nb;

    if (data->i_conv == L)
        nb = va_arg(data->list, unsigned long);
    else if (data->i_conv == LL)
        nb = va_arg(data->list, unsigned long long);
    else
        nb = va_arg(data->list, unsigned int);
    if (data->i_conv == HH)
        nb = (unsigned char)nb;
    else if (data->i_conv == H)
        nb = (unsigned short)nb;
    return (ft_uitoabase(nb, data->conversion == 'o' ? 8 : 10));
}

static void         pf_handle_base(t_printf *data, intmax_t nb)
{
    int i;

    if (data->conversion == 'c')
    {
        data->str = (char *)malloc(sizeof(char) * 2);
        *(data->str) = va_arg(data->list, int);
        *(data->str + 1) = '\0';
    }
    else if (data->conversion == 'X')
        data->str = ft_itoa_base(nb, 16);
    else if (data->conversion == 'x')
    {
        data->str = ft_itoa_base(nb, 16);
        i = -1;
        while (data->str && data->str[++i])
        {
            if (data->str[i] >= 'A' && data->str[i] <= 'Z')
                data->str[i] -= 32;
        }
    }
    else
        data->str = ft_itoa_base(nb, 10);
}

static inline void  pf_handle_string(t_printf *data)
{
    data->str = va_arg(data->list, char *);
    if (!data->str)
        data->str = data->precision > 0 ? "(null)" : "";
}

void                pf_get_type(t_printf *data)
{
    intmax_t    nb;

    if (pf_strchr("cdixX", data->conversion))
    {
        if (data->i_conv == L)
            nb = va_arg(data->list, long);
        else if (data->i_conv == LL)
            nb = va_arg(data->list, long long);
        else
            nb = va_arg(data->list, int);
        if (data->i_conv == HH)
            nb = (char)nb;
        else if (data->i_conv == H)
            nb = (short)nb;
        pf_handle_base(data, nb);
    }
    else if (data->conversion == 'o' || data->conversion == 'u')
        data->str = pf_unsigned_type(data);
    else if (data->conversion == 'p')
        data->str = ft_itoa_base((intmax_t)va_arg(data->list, void *), 16);
    else if (data->conversion == 's')
        pf_handle_string(data);
    data->len = pf_strlen(data->str, 0);
}
