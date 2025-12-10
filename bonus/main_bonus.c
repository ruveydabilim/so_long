/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 16:35:26 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/10 16:35:41 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	main(int argc, char **argv)
{
	char	**map;
	char	**mapcpy;
	t_map	*map_values;
	t_map	*cpymaps;

	if (argc != 2)
		return (ft_printf("Error\nInvalid argument count.\n"), 1);
	map = map_parser(argv[1]);
	if (!map)
		return (1);
	mapcpy = map_parser(argv[1]);
	if (!mapcpy)
		return (free_doublepoint((void **)map), 1);
	cpymaps = ft_calloc(sizeof(t_map), 1);
	if (!cpymaps)
		return (free_doublepoint((void **)map),
			free_doublepoint((void **)mapcpy), 1);
	map_values = map_validation(map, mapcpy, cpymaps);
	free_doublepoint((void **)mapcpy);
	if (!map_values)
		return (free_doublepoint((void **)map), 1);
	so_long(map, map_values);
	free_all(map_values);
	return (0);
}