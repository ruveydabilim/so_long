/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:11:45 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/11 12:20:54 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putnbr(int n, int fd, int *len)
{
	if (n == -2147483648)
	{
		ft_putstr("-2147483648", 1, len);
		return ;
	}
	if (n < 0)
	{
		n = -n;
		ft_putchar('-', fd, len);
	}
	if (n >= 10)
		ft_putnbr(n / 10, fd, len);
	ft_putchar(n % 10 + '0', fd, len);
}
