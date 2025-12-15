/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:51:40 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/15 11:26:10 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	init_maps(t_map *maps)
{
	maps->collectibles = 0;
	maps->exit.count = 0;
	maps->player.count = 0;
	maps->move_count = 0;
	maps->map_height = 0;
	maps->map_width = 0;
	maps->enemy_count = 0;
	maps->current_frame = 0;
	maps->map = NULL;
	maps->collectible = NULL;
	maps->enemies = NULL;
	maps->window = NULL;
	maps->init = NULL;
}

void	xpm_control(t_map *map_values)
{
	int	i;

	if (!map_values->imgptr.exit_open || !map_values->imgptr.wall
		|| !map_values->imgptr.floor || !map_values->imgptr.exit
		|| !map_values->imgptr.collectible || !map_values->imgptr.player
		|| !map_values->imgptr.movecount_bg || !map_values->imgptr.firstline)
		(free_all(map_values), exit(EXIT_FAILURE));
	i = 0;
	while (i < 5)
	{
		if (!map_values->imgptr.enemy[i])
			(free_all(map_values), exit(EXIT_FAILURE));
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (!map_values->imgptr.digits[i])
			(free_all(map_values), exit(EXIT_FAILURE));
		i++;
	}
}

static void	init_images2(t_map *map_values, int width, int height, int i)
{
	char	*base = "./textures/0.xpm";
	char	path[20];
	int		j;

	width = 64;
	height = 64;
	map_values->imgptr.firstline = mlx_xpm_file_to_image(map_values->init,
			"./textures/firstline.xpm", &width, &height);
	width = 128;
	height = 64;
	map_values->imgptr.movecount_bg = mlx_xpm_file_to_image(map_values->init,
			"./textures/movecount.xpm", &width, &height);
	i = -1;
	while (++i < 10)
	{


		width = 16;
		height = 32;
		j = 0;
		while (base[j])
		{
			path[j] = base[j];
			j++;
		}
		path[11] = '0' + i;
		path[j] = '\0';
		map_values->imgptr.digits[i] = mlx_xpm_file_to_image(map_values->init,
				path, &width, &height);
	}
}

static void	init_images(t_map *map_values)
{
	int		width;
	int		height;
	int		i;

	width = 64;
	height = 64;
	map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init,
			PLAYER, &width, &height);
	map_values->imgptr.collectible = mlx_xpm_file_to_image(map_values->init,
			COLL, &width, &height);
	map_values->imgptr.exit = mlx_xpm_file_to_image(map_values->init,
			EXIT, &width, &height);
	map_values->imgptr.floor = mlx_xpm_file_to_image(map_values->init,
			FLOOR, &width, &height);
	map_values->imgptr.wall = mlx_xpm_file_to_image(map_values->init,
			WALL, &width, &height);
	map_values->imgptr.exit_open = mlx_xpm_file_to_image(map_values->init,
			EXIT_OPEN, &width, &height);
	map_values->imgptr.enemy[0] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS1, &width, &height);
	map_values->imgptr.enemy[1] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS2, &width, &height);
	map_values->imgptr.enemy[2] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS3, &width, &height);
	map_values->imgptr.enemy[3] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS4, &width, &height);
	map_values->imgptr.enemy[4] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS5, &width, &height);
	init_images2(map_values, width, height, i);
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
	display_move_count(map_values);
}
