/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:08:08 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/20 10:15:23 by rbilim           ###   ########.fr       */
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

static int	is_enemy_blocking(t_map *map_values, int x, int y, int current)
{
	int	i;

	i = 0;
	while (i < map_values->enemy_count)
	{
		if (i != current && map_values->enemies[i].x == x
			&& map_values->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

void	move_enemies(t_map *map_values)
{
	int	i;
	int	x;
	int	y;
	int	n_y;

	i = -1;
	while (++i < map_values->enemy_count)
	{
		x = map_values->enemies[i].x;
		y = map_values->enemies[i].y;
		n_y = y + map_values->enemies[i].direction;
		if (map_values->map[x][n_y] == '1'
			|| map_values->map[x][n_y] == 'E'
			|| is_enemy_blocking(map_values, x, n_y, i))
			map_values->enemies[i].direction *= -1;
		else
		{
			if (map_values->map[x][n_y] == 'P')
				exit_message(map_values, 0);
			map_values->enemies[i].y = n_y;
		}
	}
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
	map_values->init = init;
	mlx_get_screen_size(init, &x, &y);
	if ((map_values->map_height + 2) * 64 > y
		|| (map_values->map_width) * 64 > x)
		(ft_putendl_fd(BIGMAPERROR, 2),
			free_all(map_values), exit(EXIT_FAILURE));
	window = mlx_new_window(init, map_values->map_width * 64,
			(map_values->map_height + 1) * 64, "SO LONG");
	if (!window)
		return (free_all(map_values), NULL);
	map_values->window = window;
	init_window(map_values, map);
	mlx_hook(window, 2, (1L << 0), handle_key, map_values);
	mlx_hook(window, 17, 0, close_window, map_values);
	mlx_loop_hook(init, enemy_movement, map_values);
	mlx_loop(init);
	return (NULL);
}
