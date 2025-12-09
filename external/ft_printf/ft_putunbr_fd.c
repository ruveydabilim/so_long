/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunbr_fd.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:15:29 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/11 12:20:07 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_putunbr_fd(unsigned int n, int fd, int *len)
{
	if (n >= 10)
		ft_putunbr_fd(n / 10, fd, len);
	ft_putchar(n % 10 + '0', fd, len);
}
