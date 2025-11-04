/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/04 17:10:25 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_maps(t_map *maps)
{
	maps->collectibles = 0;
	maps->exit.count = 0;
	maps->player.count = 0;
	maps->move_count = 0;
	maps->map_height = 0;
	maps->map_width = 0;
	maps->map = NULL;
	maps->collectible = NULL;
	maps->window = NULL;
	maps->init = NULL;
}

void	init_images(t_map *map_values)
{
	int		width;
	int		height;

	width = 64;
	height = 64;
	map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init, \
		"./textures/players.xpm", &width, &height);
	map_values->imgptr.collectible = mlx_xpm_file_to_image(map_values->init, \
		"./textures/collectible.xpm", &width, &height);
	map_values->imgptr.exit = mlx_xpm_file_to_image(map_values->init, \
		"./textures/exit.xpm", &width, &height);
	map_values->imgptr.floor = mlx_xpm_file_to_image(map_values->init, \
		"./textures/floor.xpm", &width, &height);
	map_values->imgptr.wall = mlx_xpm_file_to_image(map_values->init, \
		"./textures/wall.xpm", &width, &height);
	map_values->imgptr.exit_open = mlx_xpm_file_to_image(map_values->init, \
		"./textures/exit_open.xpm", &width, &height);
}

void	init_window(t_map *map_values, char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	init_images(map_values);
	while (map[x])
	{
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			control_map(map_values, map[x][y], x, y);
			y++;
		}
		x++;
	}
}

void	redraw_window(t_map *map_values, char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx_clear_window(map_values->init, map_values->window);
	while (map[x])
	{
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			control_map(map_values, map[x][y], x, y);
			y++;
		}
		x++;
	}
}
