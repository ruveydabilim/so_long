/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:51:39 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/20 10:12:55 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_doubleptr(char **ptr)
{
	int	i;

	i = 0;
	if (!ptr || !ptr[i])
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	freemsg(void *free1, void *free2, char *message)
{
	if (free1)
		free(free1);
	if (free2)
		free(free2);
	if (message)
		ft_putendl_fd(message, 2);
}

void	exit_message(t_map *map_values)
{
	ft_printf(WONGAME);
	free_all(map_values);
	exit(0);
}

void	free_images(t_map *map_values)
{
	if (!map_values->init)
		return ;
	if (map_values->imgptr.player_default)
		mlx_destroy_image(map_values->init, map_values->imgptr.player_default);
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
	if (map_values->imgptr.move_up)
		mlx_destroy_image(map_values->init, map_values->imgptr.move_up);
	if (map_values->imgptr.move_left)
		mlx_destroy_image(map_values->init, map_values->imgptr.move_left);
	if (map_values->imgptr.move_down)
		mlx_destroy_image(map_values->init, map_values->imgptr.move_down);
}

void	free_all(t_map *map_values)
{
	if (!map_values)
		return ;
	if (map_values->init)
	{
		free_images(map_values);
		if (map_values->window)
			mlx_destroy_window(map_values->init, map_values->window);
		mlx_destroy_display(map_values->init);
	}
	if (map_values->map)
		free_doubleptr(map_values->map);
	if (map_values->collectible)
		free(map_values->collectible);
	free(map_values->init);
	free(map_values);
}
