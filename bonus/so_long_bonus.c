/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:08:08 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/14 17:51:21 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	handle_key( int keycode, t_map *map_value)
{
	if (keycode == 65307)
		return (free_all(map_value), exit(0), 1);
	if (keycode == 119)
		return (press_key(map_value, 'W'), 0);
	if (keycode == 115)
		return (press_key(map_value, 'S'), 0);
	if (keycode == 97)
		return (press_key(map_value, 'A'), 0);
	if (keycode == 100)
		return (press_key(map_value, 'D'), 0);
	return (0);
}

static int	close_window(t_map *map_value)
{
	return (free_all(map_value), exit(0), 0);
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

void	move_enemies(t_map *map_values)
{
	int	i;
	int	x;
	int	y;

	if (!map_values->enemies || map_values->enemy_count == 0)
		return ;
	i = 0;
	while (i < map_values->enemy_count)
	{
		x = map_values->enemies[i].x;
		y = map_values->enemies[i].y;
		if (map_values->map[x + 1][y] == '0'
			|| map_values->map[x + 1][y] == 'P')
		{
			if (map_values->map[x + 1][y] == 'P')
				close_window(map_values);
			map_values->map[x][y] = '0';
			map_values->enemies[i].x += 1;
			map_values->map[x + 1][y] = 'X';
		}
		i++;
	}

}

int	enemy_movement(t_map *map_values)
{
	static int	counter;
	static int	move_counter;

	counter++;
	if (counter >= 1000)
	{
		map_values->current_frame++;
		if (map_values->current_frame >= 5)
			map_values->current_frame = 0;
		counter = 0;
	}
	move_counter++;
	if (move_counter >= 1000)
	{
		move_enemies(map_values);
		move_counter = 0;
	}
	redraw_window(map_values);
	return (0);
}

void	*so_long(char **map, t_map *map_values)
{
	void	*init;
	void	*window;
	int		x;
	int		y;

	init = mlx_init();
	if (!init)
		return (NULL);
	mlx_get_screen_size(init, &x, &y);
	if (map_values->map_height * 64 > y
		|| map_values->map_width * 64 > x)
		return (mlx_destroy_display(init), free(init),
			freemsg(NULL, NULL, "Error\nMap is too big"), NULL);
	window = mlx_new_window(init, map_values->map_width * 64,
			map_values->map_height * 64, "SO LONG");
	map_values->init = init;
	if (!window)
		return (NULL);
	map_values->window = window;
	init_window(map_values, map);
	mlx_hook(window, 2, (1L << 0), handle_key, map_values);
	mlx_hook(window, 17, 0, close_window, map_values);
	mlx_loop_hook(init, enemy_movement, map_values);
	mlx_loop(init);
	return (NULL);
}
