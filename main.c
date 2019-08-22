/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:51:21 by maboye            #+#    #+#             */
/*   Updated: 2019/08/22 23:35:51 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/ft_printf.h"

int             main(int ac, char **av)
{
    int     result;

    //result = printf("pf: %d\n", atoi(av[1]));
    //result = printf("pf:%10dabc%dabc\n", atoi(av[1]), 456);
    result = printf("pf:%10sabc%.sabc\n", av[1], av[1]);
    //result = printf("ft: %x\n", 5000138);
    //result = printf("ft: %p\n", &result);
    printf("result: %d\n", result);
    //printf("%p\n", &result);
    //printf("so: int %lu, so: intmax: %lu\n", sizeof(int), sizeof(uintmax_t));
    //result = ft_printf("my: %d\n", atoi(av[1]));
    //result = ft_printf("my:%10dabc%dabc\n", atoi(av[1]), 456);
    result = ft_printf("my:%10sabc%.sabc\n", av[1], av[1]);
    //result = ft_printf("my: %x\n", 5000138);
    //result = ft_printf("my: %p\n", &result);
    printf("result: %d\n", result);
    return (0);
}
