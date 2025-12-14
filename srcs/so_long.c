/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:08:08 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/14 19:47:37 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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
	mlx_put_image_to_window(map_values->init, map_values->window,
		imgptr, y * width, x * height);
	return (imgptr);
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
			freemsg(NULL, NULL, BIGMAPERROR), NULL);
	window = mlx_new_window(init, map_values->map_width * 64,
			map_values->map_height * 64, "SO LONG");
	map_values->init = init;
	if (!window)
		return (NULL);
	map_values->window = window;
	init_window(map_values, map);
	mlx_hook(window, 2, (1L << 0), handle_key, map_values);
	mlx_hook(window, 17, 0, close_window, map_values);
	mlx_loop(init);
	return (NULL);
}
