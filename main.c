/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:51:21 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 18:56:50 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

// make && gcc main.c libftprintf.a -o ft_printf
// ./ft_printf "test"

int             main(int ac, char **av)
{
    int     result;

    result = 0;
    if (ac == 2 && av[1])
        result = ft_printf(av[1]);
    printf("\nresult: %d\n", result);
    return (0);
}
