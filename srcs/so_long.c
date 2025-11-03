/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:08:08 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/03 21:59:05 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	handle_key( int keycode, t_map *map_value)
{
	if (keycode == 65307)
		return (free_all(map_value), exit(1), 1);
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

static void	*control_map(t_map *map_values, char map, int x, int y)
{
	int			width;
	int			height;
	void		*imgptr;

	imgptr = NULL;
	width = 64;
	height = 64;
		
	if (map == 'P')
		imgptr = map_values->imgptr->player;
	else if (map == 'C')
		imgptr = map_values->imgptr->collectable;
	else if (map == 'E' && map_values->collectables != 0)
		imgptr = map_values->imgptr->exit;
	else if (map == 'E' && map_values->collectables == 0)
		imgptr = map_values->imgptr->exit_open;
	else if (map == '0')
		imgptr = map_values->imgptr->floor;
	else if (map == '1')
		imgptr = map_values->imgptr->wall;
	else
		return (NULL);
	mlx_put_image_to_window(map_values->init, map_values->window, \
		imgptr, y * width, x * height);
	return (imgptr);
}
void	init_images(t_map *map_values)
{
	int		width;
	int		height;

	width = 64;
	height = 64;
	map_values->imgptr->player = mlx_xpm_file_to_image(map_values->init, \
		"./textures/players.xpm", &width, &height);
	map_values->imgptr->collectable = mlx_xpm_file_to_image(map_values->init, \
		"./textures/collectible.xpm", &width, &height);
	map_values->imgptr->exit = mlx_xpm_file_to_image(map_values->init, \
		"./textures/exit.xpm", &width, &height);
	map_values->imgptr->floor = mlx_xpm_file_to_image(map_values->init, \
		"./textures/floor.xpm", &width, &height);
	map_values->imgptr->wall = mlx_xpm_file_to_image(map_values->init, \
		"./textures/wall.xpm", &width, &height);
	map_values->imgptr->exit_open = mlx_xpm_file_to_image(map_values->init, \
		"./textures/exit_open.xpm", &width, &height);
}

void	init_window(t_map *map_values, char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
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

void	redraw_window(t_map *map_values, char **map)
{
	int		x;
	int		y;

	free_images(map_values);
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

void	*so_long(char **map, t_map *map_values)
{
	void	*init;
	void	*window;

	init = mlx_init();
	if (!init)
		return (NULL);
	map_values->init = init;
	window = mlx_new_window(init, map_values->map_width * 64, \
		map_values->map_height * 64, "SO LONG");
	if (!window)
		return (NULL);
	map_values->window = window;
	init_window(map_values, map);
	mlx_key_hook(window, handle_key, map_values);
	mlx_hook(window, 17, 0, close_window, map_values);
	mlx_loop(init);
	return (NULL);
}
