/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maboye <maboye@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/06 18:33:31 by maboye            #+#    #+#             */
/*   Updated: 2019/08/06 19:10:28 by maboye           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/ft_printf.h"

static void		pf_parse_flag(const char *format, t_printf *data, int *i, int *res)
{
	(void)res;
	while (pf_is_flag(format[*i]))
	{
		//exit if the same flag is set multiple times
		//add other flags
		printf("flag symbol %c\n", format[*i]);
		if ((format[*i] == '#') && !(data->flags & HASH))
				data->flags += HASH;
		else if ((format[*i] == '0') && !(data->flags & ZERO))
				data->flags += ZERO;
		else if ((format[*i] == '-') && !(data->flags & LESS))
				data->flags += LESS;
		else if ((format[*i] == '+') && !(data->flags & MORE))
				data->flags += MORE;
		else if ((format[*i] == ' ') && !(data->flags & SPC))
				data->flags += SPC;
		else if ((format[*i] == 39) && !(data->flags & APOST))
				data->flags += APOST;
		else
			printf("will add EXIT\n");//res -1 instead of exit?
		(*i)++;
	}

}

static void		pf_parse_width(const char *format, t_printf *data, int *i, int *res)
{
//if the value is more than INT MAX it is left at the value of INT_MAX and not changed further
	long long	width;
	(void)res;
	width = 0;
	while (pf_isdigit(format[*i]) && width <= 2147483647)
	{
		width = (10 * width) + (format[*i] - '0');
		(*i)++;
	}
	if (width > 2147483647)
		width = 2147283647;
	data->width = width;
}	

static void		pf_parse_precision(const char *format, t_printf *data, int *i, int *res)
{
//if the value is more than INT MAX it is left at the value of INT_MAX and not changed further
	long long	precision;
	(void)res;
	if (format[*i] == '.')
       	{
		(*i)++;
		precision = 0;
		while (pf_isdigit(format[*i]) && precision <= 2147483647)
		{
			precision = (10 * precision) + (format[*i] - '0');
			(*i)++;
		}
		if (precision > 2147483647)
			precision = 2147283647;
		data->precision = precision;
	}
}	

static void		pf_parse_size(const char *format, t_printf *data, int *i, int *res)
{
	(void)res;
	if (format[*i] == 'l' || format[*i] == 'h' || format [*i] == 'L')
	{
		if (format[*i] == 'L')
			data->i_conv = LF;
		else 
			data->i_conv = (format[*i] == 'l') ? L : H;
		(*i)++;
	}
	if ((format[*i] == 'l' || format[*i] == 'h') && (data->i_conv != LF))
	{
		data->i_conv = (format[*i] == 'l') ? LL : HH;
		(*i)++;
	}

}	

static void		pf_validate_flags(t_printf *data, int *res)
{
	(void)res;
	if ((data->flags & HASH) && (data->conversion == 'c' || data->conversion == 'd' ||
				data->conversion == 'i' || data->conversion == 'u' ||
				data->conversion == 's'))
		printf("Invalid according to the last flag check\n");//exit
	if (((data->flags & ZERO) && (data->flags & LESS)) || 
		       ((data->flags & SPC) && (data->flags & MORE)))	
		printf("Invalid according to the last flag check\n");//exit
	if ((data->flags & ZERO) && (data->conversion == 'i' || data->conversion == 'u' ||
			data->conversion == 'x' || data->conversion == 'X' ||
			data->conversion == 'o' || data->conversion == 'o') &&
			data->precision >= 0) // >= !!! initialize precision to -1
		printf("Invalid according to the last flag check\n");//exit
	if ((data->flags & APOST) && (data->conversion != 'u' &&
			data->conversion != 'd' && data->conversion != 'f')) 
		printf("Invalid according to the last flag check\n");//exit


}

static void		pf_parse_conversion(const char *format, t_printf *data, int *i, int *res)
{
	(void)res;
	if ((format[*i] == 'd' || format[*i] == 'i' || format[*i] == 'o' ||
			format[*i] == 'u' || format[*i] == 'x' || format[*i] == 'X') &&
			(data->i_conv != LF))
		data->conversion = format[(*i)++];
	else if ((format[*i] == 'f') && (data->i_conv != LL && data->i_conv != H &&
			data->i_conv != HH)) 
		data->conversion = format[(*i)++];
	else if (format[*i] == 'c' || format[*i] == 's' || format[*i] == 'p')
		data->conversion = format[(*i)++];
	else
		printf("conversion is not valid\n"); //exit
	pf_validate_flags(data, res);
}

static void		pf_parsing(const char *format, t_printf *data, int *i, int *res)
{
	data->precision = -1;
	pf_parse_flag(format, data, i, res);
	pf_parse_width(format, data, i, res);
	pf_parse_precision(format, data, i, res);
	pf_parse_size(format, data, i, res);
	pf_parse_conversion(format, data, i, res);
	pf_handler(data);
}

int				pf_parser(const char *format, t_printf *data)
{
	int	result;
	int	i;

	result = 0;
	i = 0;
	while (format && format[i])
	{
		if (format[i] == '%')
		{
			++i;
            		++result;
			if (!format[i])
				break ;
			else if (format[i] == '%')
			{
				write(1, &format[i++], 1);
				++result;
			}
			else
				pf_parsing(format, data, &i, &result);
		}
		else
        	{
			write(1, &format[i++], 1);
		    ++result;
       		 }
	}
	int u = 123;
	printf("\n\n Testing: %'d", u);
	printf("flags value is %d\n", data->flags);
	printf("final width is: %ld\n", data->width);
	printf("final precision is: %d\n", data->precision);
	printf("final size is: %d\n", data->i_conv);
	printf("final conversion is: %c\n", data->conversion);


	return (result);
}
