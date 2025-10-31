/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:08:08 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/31 18:18:13 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	handle_key(t_map *map_value, int keycode)
{
	if (keycode == 65307)
		return (exit(1), 1); //burada da her şeyi freele
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

static int	close_window(void)
{
	//burada her şeyi freelemelisin!!!
	return (exit(0), 0);
}

static void	control_map(void *ptr, void *ptr2, char map, int x, int y)
{
	int			width;
	int			height;
	void		*imgptr;

	imgptr = NULL;
	width = 16;
	height = 16;
	if (map == 'P')
		imgptr = mlx_xpm_file_to_image(ptr, "./textures/player.xpm", \
			&width, &height);
	else if (map == 'C')
		imgptr = mlx_xpm_file_to_image(ptr, "./textures/collectable.xpm", \
			&width, &height);
	else if (map == 'E')
		imgptr = mlx_xpm_file_to_image(ptr, "./textures/collectable.xpm", \
			&width, &height);
	else if (map == '0')
		imgptr = mlx_xpm_file_to_image(ptr, "./textures/floor.xpm", \
			&width, &height);
	else if (map == '1')
		imgptr = mlx_xpm_file_to_image(ptr, "./textures/wall.xpm", \
			&width, &height);
	else
		return ;
	mlx_put_image_to_window(ptr, ptr2, imgptr, x * width, y * height);
}

static void	function(void *ptr, void *ptr2, char **map)
{
	int		x;
	int		y;


	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y])
		{
			control_map(ptr, ptr2, map[x][y], x, y);
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
	window = mlx_new_window(init, 2000, 2000, "game");
	if (!window)
		return (NULL);
	w(init, window, map);
	mlx_key_hook(window, handle_key, NULL);
	mlx_hook(window, 17, 0, close_window, NULL);
	mlx_loop(init);
	return (NULL);
}
