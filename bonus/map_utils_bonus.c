/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/14 23:58:20 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	update_img(t_map *map_values, int key)
{
	int		width;
	int		height;

	width = 64;
	height = 64;
	if (map_values->imgptr.player)
		mlx_destroy_image(map_values->init, map_values->imgptr.player);
	if (key == 'W')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init,
				MOVE_UP, &width, &height);
	else if (key == 'A')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init,
				MOVE_LEFT, &width, &height);
	else if (key == 'S')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init,
				MOVE_DOWN, &width, &height);
	else if (key == 'D')
		map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init,
				PLAYER, &width, &height);
	xpm_control(map_values);
}

void	*control_map(t_map *map_values, char map, int x, int y)
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
		imgptr = map_values->imgptr.enemy[map_values->current_frame];
	mlx_put_image_to_window(map_values->init, map_values->window,
		imgptr, y * width, x * height);
	return (imgptr);
}

int	redraw_window(t_map *map_values)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	mlx_clear_window(map_values->init, map_values->window);
	while (map_values->map[x])
	{
		y = 0;
		while (map_values->map[x][y] && map_values->map[x][y] != '\n')
		{
			control_map(map_values, map_values->map[x][y], x, y);
			y++;
		}
		x++;
	}
	return (0);
}
