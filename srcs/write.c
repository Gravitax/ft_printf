/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 16:40:49 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 17:16:12 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

int				pf_write(const char *str, size_t len)
{
	write(1, str, len);
	return (len);
}

int				pf_repeat(const char c, size_t len)
{
	int i;

	i = -1;
	while (++i < (int)len)
		pf_write(&c, 1);
	return (i);
}
