/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/11 12:14:27 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/12 22:54:30 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <unistd.h>

int		ft_printf(const char *format, ...);
void	ft_putchar(int c, int fd, int *len);
void	ft_putnbr(int n, int fd, int *len);
void	ft_putunbr_fd(unsigned int n, int fd, int *len);
void	ft_putstr(char *s, int fd, int *len);
void	ft_puthex_fd(long n, int fd, int *len, char format);
void	ft_putmem_fd(void *ptr, int fd, int *len);

#endif