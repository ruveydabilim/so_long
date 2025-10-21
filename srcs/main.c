/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:23:10 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/21 18:19:44 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	**map;
	char	**mapcpy;

	if (argc != 2)
		return (ft_printf("error! invalid arguman count."), 1);
	map = map_parser(argv[1]);
	mapcpy = map_parser(argv[1]);
	if (!map)
		return (1);
	if (!map_validation(mapcpy))
		return (1);
}
