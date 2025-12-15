/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/15 23:29:04 by rbilim           ###   ########.fr       */
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
		imgptr, y * width, (x + 1) * height);
	return (imgptr);
}

int	redraw_window(t_map *map_values)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
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
