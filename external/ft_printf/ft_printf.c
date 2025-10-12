/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:13:35 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/11 12:19:36 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static void	checkformat(va_list args, char c, int *len)
{
	if (c == 'd' || c == 'i')
		ft_putnbr(va_arg(args, int), 1, len);
	else if (c == 'c')
		ft_putchar(va_arg(args, int), 1, len);
	else if (c == 's')
		ft_putstr(va_arg(args, char *), 1, len);
	else if (c == 'x' || c == 'X')
		ft_puthex_fd(va_arg(args, int), 1, len, c);
	else if (c == 'p')
		ft_putmem_fd(va_arg(args, void *), 1, len);
	else if (c == 'u')
		ft_putunbr_fd(va_arg(args, int), 1, len);
	else if (c == '%')
		ft_putchar('%', 1, len);
	else
	{
		ft_putchar('%', 1, len);
		ft_putchar(c, 1, len);
	}
}

int	ft_printf(const char *format, ...)
{
	va_list	args;
	int		i;
	int		len;

	len = 0;
	i = 0;
	va_start(args, format);
	while (format[i])
	{
		if (format[i] == '%')
		{
			if (format[++i])
				checkformat(args, format[i], &len);
			else
			{
				va_end(args);
				return (-1);
			}
		}
		else
			ft_putchar(format[i], 1, &len);
		i++;
	}
	va_end(args);
	return (len);
}
