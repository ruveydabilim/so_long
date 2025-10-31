/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:23:10 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/31 16:55:28 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"
#include <stdio.h>
#include <string.h>

int	main(int argc, char **argv)
{
	char	**map;
	char	**mapcpy;
	t_map	*map_values;

	if (argc != 2)
		return (ft_printf("error! invalid arguman count."), 1);
	map = map_parser(argv[1]);
	if (!map)
		return (ft_printf("error!"), 1);
	mapcpy = map_parser(argv[1]);
	if (!mapcpy)
		return (ft_printf("error!"), 1);
	map_values = map_validation(mapcpy);
	if (!map_values)
		return (1);
	so_long(map, map_values);
	//mapcpy i yok edecek fonksiyon buraya.
}
