/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:14:55 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/11 12:19:58 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_puthex_fd(long n, int fd, int *len, char format)
{
	char	*hex;

	if (format == 'X')
		hex = "0123456789ABCDEF";
	else
		hex = "0123456789abcdef";
	if (n < 0)
		n += 4294967296;
	if (n >= 16)
		ft_puthex_fd(n / 16, fd, len, format);
	ft_putchar(hex[n % 16], fd, len);
}
