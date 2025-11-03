/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:51:39 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/03 22:01:00 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	free_doublepoint(void **ptr)
{
	int	i;

	i = 0;
	if (!ptr || !ptr[i])
		return ;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

void	free_images(t_map *map_values)
{
	if (!map_values->init || !map_values->imgptr)
		return ;
	if (map_values->imgptr->player)
		mlx_destroy_image(map_values->init, map_values->imgptr->player);
	if (map_values->imgptr->collectable)
		mlx_destroy_image(map_values->init, map_values->imgptr->collectable);
	if (map_values->imgptr->exit)
		mlx_destroy_image(map_values->init, map_values->imgptr->exit);
	if (map_values->imgptr->floor)	
		mlx_destroy_image(map_values->init, map_values->imgptr->floor);
	if (map_values->imgptr->wall)
		mlx_destroy_image(map_values->init, map_values->imgptr->wall);
	if (map_values->imgptr->exit_open)
		mlx_destroy_image(map_values->init, map_values->imgptr->exit_open);
	if (map_values->imgptr)
		mlx_destroy_image(map_values->init, map_values->imgptr);
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
		free_doublepoint((void **)map_values->map);
	if (map_values->collectable)
		free(map_values->collectable);
	free(map_values->imgptr);
	free(map_values->init);
	free(map_values);
}
