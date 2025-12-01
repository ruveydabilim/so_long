/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/01 18:03:59 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	update_img(t_map *map_values, int key)
{
	int		width;
	int		height;

	width = 64;
	height = 64;
	if (map_values->imgptr.player)
		mlx_destroy_image(map_values->init, map_values->imgptr.player);
	if (key == 'W')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init, \
"./textures/move_up.xpm", &width, &height);
	else if (key == 'A')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init, \
"./textures/move_left.xpm", &width, &height);
	else if (key == 'S')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init, \
"./textures/move_down.xpm", &width, &height);
	else if (key == 'D')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init, \
"./textures/players.xpm", &width, &height);
	xpm_control(map_values);
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
