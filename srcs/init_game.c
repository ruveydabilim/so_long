/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:51:40 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/19 14:06:35 by rbilim           ###   ########.fr       */
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
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.wall)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.floor)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.exit)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.collectible)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.player)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.player_default)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.move_up)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.move_left)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else if (!map_values->imgptr.move_down)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	else
		return ;
}

static void	init_images(t_map *map_values)
{
	int		width;
	int		height;

	width = 64;
	height = 64;
	map_values->imgptr.player_default = mlx_xpm_file_to_image(map_values->init,
			PLAYER, &width, &height);
	map_values->imgptr.player = map_values->imgptr.player_default;
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
	map_values->imgptr.move_up = mlx_xpm_file_to_image(map_values->init,
			MOVE_UP, &width, &height);
	map_values->imgptr.move_left = mlx_xpm_file_to_image(map_values->init,
			MOVE_LEFT, &width, &height);
	map_values->imgptr.move_down = mlx_xpm_file_to_image(map_values->init,
			MOVE_DOWN, &width, &height);
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
