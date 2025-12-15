/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/15 23:46:23 by rbilim           ###   ########.fr       */
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

static int	is_enemy_position(t_map *map_values, int x, int y)
{
	int	i;

	i = 0;
	while (i < map_values->enemy_count)
	{
		if (map_values->enemies[i].x == x && map_values->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

int	redraw_window(t_map *map_values)
{
	int		x;
	int		y;
	char	tile;

	x = 0;
	y = 0;
	while (map_values->map[x])
	{
		y = 0;
		while (map_values->map[x][y] && map_values->map[x][y] != '\n')
		{
			if (is_enemy_position(map_values, x, y))
				tile = 'X';
			else
				tile = map_values->map[x][y];
			control_map(map_values, tile, x, y);
			y++;
		}
		x++;
	}
	return (0);
}

static int	count_to_digits(int count, int *digits)
{
	int	i;

	i = 0;
	if (count == 0)
		digits[i++] = 0;
	else
	{
		while (count > 0 && i < 10)
		{
			digits[i++] = count % 10;
			count /= 10;
		}
	}
	return (i);
}

void	display_move_count(t_map *map_values)
{
	int		digits[10];
	int		i;
	int		x_pos;

	x_pos = 0;
	while (x_pos < map_values->map_width * 64)
	{
		mlx_put_image_to_window(map_values->init, map_values->window,
			map_values->imgptr.firstline, x_pos, 0);
		x_pos += 64;
	}
	i = count_to_digits(map_values->move_count, digits);
	x_pos = 0;
	mlx_put_image_to_window(map_values->init, map_values->window,
		map_values->imgptr.movecount_bg, x_pos, 0);
	x_pos += 128;
	while (--i >= 0)
	{
		mlx_put_image_to_window(map_values->init, map_values->window,
			map_values->imgptr.digits[digits[i]], x_pos, 0);
		x_pos += 16;
	}
}
