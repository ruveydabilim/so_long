/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:51:40 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/01 18:01:40 by rbilim           ###   ########.fr       */
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

void	xpm_control(t_map *map_values)
{
	if (!map_values->imgptr.exit_open)
		(free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.wall)
		(free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.floor)
		(free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.exit)
		(free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.collectible)
		(free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.player)
		(free_all(map_values), exit(EXIT_FAILURE));
	else
		return ;
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
	xpm_control(map_values);
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
