/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/12 14:31:35 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/12 18:31:23 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	xpm_control_bonus(t_map *map_values)
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

void	*control_map_bonus(t_map *map_values, char map, int x, int y)
{
	int			width;
	int			height;
	void		*imgptr;

	imgptr = NULL;
	width = 64;
	height = 64;
	if (map == 'P')
		imgptr = map_values->imgptr.player;
	else if (map == 'C')
		imgptr = map_values->imgptr.collectible;
	else if (map == 'E' && map_values->collectibles != 0)
		imgptr = map_values->imgptr.exit;
	else if (map == 'E' && map_values->collectibles == 0)
		imgptr = map_values->imgptr.exit_open;
	else if (map == '0')
		imgptr = map_values->imgptr.floor;
	else if (map == '1')
		imgptr = map_values->imgptr.wall;
	else if (map == 'X')
		imgptr = map_values->imgptr.enemy[0];
	mlx_put_image_to_window(map_values->init, map_values->window,
		imgptr, y * width, x * height);
	return (imgptr);
}

static void	init_images(t_map *map_values)
{
	int		width;
	int		height;

	width = 64;
	height = 64;
	map_values->imgptr.enemy[0] = mlx_xpm_file_to_image(map_values->init, \
"./textures/enemy1.xpm", &width, &height);
	map_values->imgptr.enemy[1] = mlx_xpm_file_to_image(map_values->init, \
"./textures/enemy2.xpm", &width, &height);
	map_values->imgptr.enemy[2] = mlx_xpm_file_to_image(map_values->init, \
"./textures/enemy3.xpm", &width, &height);
	map_values->imgptr.enemy[3] = mlx_xpm_file_to_image(map_values->init, \
"./textures/enemy4.xpm", &width, &height);
	map_values->imgptr.enemy[4] = mlx_xpm_file_to_image(map_values->init, \
"./textures/enemy5.xpm", &width, &height);
	xpm_control(map_values);
}

void	init_window_bonus(t_map *map_values, char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	init_window(map_values, map);
	init_images(map_values);
	while (map[x])
	{
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			control_map_bonus(map_values, map[x][y], x, y);
			y++;
		}
		x++;
	}
}
