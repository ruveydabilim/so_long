/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_utils_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:50:43 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/15 16:16:23 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	free_images(t_map *map_values)
{
	if (!map_values->init)
		return ;
	if (map_values->imgptr.player)
		mlx_destroy_image(map_values->init, map_values->imgptr.player);
	if (map_values->imgptr.collectible)
		mlx_destroy_image(map_values->init, map_values->imgptr.collectible);
	if (map_values->imgptr.exit)
		mlx_destroy_image(map_values->init, map_values->imgptr.exit);
	if (map_values->imgptr.floor)
		mlx_destroy_image(map_values->init, map_values->imgptr.floor);
	if (map_values->imgptr.wall)
		mlx_destroy_image(map_values->init, map_values->imgptr.wall);
	if (map_values->imgptr.exit_open)
		mlx_destroy_image(map_values->init, map_values->imgptr.exit_open);
	if (map_values->imgptr.movecount_bg)
		mlx_destroy_image(map_values->init, map_values->imgptr.movecount_bg);
	if (map_values->imgptr.firstline)
		mlx_destroy_image(map_values->init, map_values->imgptr.firstline);
}

static void	init_numberimages(t_map *map_values, int width, int height, int i)
{
	char	*base;
	char	path[20];
	int		j;

	base = "./textures/0.xpm";
	width = 64;
	height = 64;
	map_values->imgptr.firstline = mlx_xpm_file_to_image(map_values->init,
			"./textures/firstline.xpm", &width, &height);
	width = 128;
	map_values->imgptr.movecount_bg = mlx_xpm_file_to_image(map_values->init,
			"./textures/movecount.xpm", &width, &height);
	i = -1;
	while (++i < 10)
	{
		width = 16;
		height = 32;
		j = -1;
		while (base[++j])
			path[j] = base[j];
		path[11] = '0' + i;
		path[j] = '\0';
		map_values->imgptr.digits[i] = mlx_xpm_file_to_image(map_values->init,
				path, &width, &height);
	}
}

static void	init_enemies(t_map *map_values, int width, int height)
{
	map_values->imgptr.enemy[0] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS1, &width, &height);
	map_values->imgptr.enemy[1] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS2, &width, &height);
	map_values->imgptr.enemy[2] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS3, &width, &height);
	map_values->imgptr.enemy[3] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS4, &width, &height);
	map_values->imgptr.enemy[4] = mlx_xpm_file_to_image(map_values->init,
			ENEMYS5, &width, &height);
}

void	init_images(t_map *map_values)
{
	int		width;
	int		height;
	int		i;

	i = 0;
	width = 64;
	height = 64;
	map_values->imgptr.player = mlx_xpm_file_to_image(map_values->init,
			PLAYER, &width, &height);
	map_values->imgptr.collectible = mlx_xpm_file_to_image(map_values->init,
			COLL, &width, &height);
	map_values->imgptr.exit = mlx_xpm_file_to_image(map_values->init,
			EXIT, &width, &height);
	map_values->imgptr.floor = mlx_xpm_file_to_image(map_values->init,
			FLOOR, &width, &height);
	map_values->imgptr.wall = mlx_xpm_file_to_image(map_values->init,
			WALL, &width, &height);
	map_values->imgptr.exit_open = mlx_xpm_file_to_image(map_values->init,
			EXIT_OPEN, &width, &height);
	init_numberimages(map_values, width, height, i);
	init_enemies(map_values, width, height);
	xpm_control(map_values);
}
