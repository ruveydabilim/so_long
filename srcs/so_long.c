/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:08:08 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/28 17:46:52 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	ext(int keycode)
{
	if (keycode == 65307)
		return (exit(0), 1);
	if (keycode == 119)
		ft_printf("up\n");
	if (keycode == 115)
		ft_printf("down\n");
	if (keycode == 97)
		ft_printf("left\n");
	if (keycode == 100)
		ft_printf("right\n");
	return (0);
}

static int	close_window(void)
{
	return (exit(0), 0);
}

static void	control_map(void *ptr, void *ptr2, char map, int x, int y)
{
	int			width;
	int			height;
	void		*imgptr;
	static int	i = 0;

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

void	*so_long(char **map)
{
	void	*ptr;
	void	*ptr2;

	ptr = mlx_init();
	if (!ptr)
		return (NULL);
	ptr2 = mlx_new_window(ptr, 1000, 1000, "game");
	if (!ptr2)
		return (NULL);
	function(ptr, ptr2, map);
	mlx_key_hook(ptr2, ext, NULL);
	mlx_hook(ptr2, 17, 0, close_window, NULL);
	mlx_loop(ptr);
	return (NULL);
}
