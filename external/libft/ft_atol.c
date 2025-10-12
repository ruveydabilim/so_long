/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/31 19:34:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/11 18:01:02 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_controlif(long rest, int s, char c)
{
	if (s == 1 && (rest > 922337203685477580
			|| (rest == 922337203685477580 && (c) > '7')))
		return (-1);
	if (s == -1 && (rest > 922337203685477580
			|| (rest == 922337203685477580 && (c) > '8')))
		return (0);
	return (1);
}

long	ft_atol(const char *str)
{
	long	rest;
	size_t	i;
	int		s;
	int		control;

	i = 0;
	s = 1;
	rest = 0;
	if (!str || !str[0])
		return (2147483648);
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i++] == '-')
			s = -s;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		control = ft_controlif(rest, s, str[i]);
		if (control == 0 || control == -1)
			return (2147483648);
		rest = (str[i++] - '0') + (rest * 10);
	}
	return (rest * s);
}
