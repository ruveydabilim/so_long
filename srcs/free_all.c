/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:51:39 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/01 20:50:15 by rbilim           ###   ########.fr       */
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

void	free_all(t_map *map_values, int flag)
{
	int	i;

	if (!map_values)
		return ;
	i = 0;
	if (flag)
	{
		if (map_values->imgptr)
		{
			while (map_values->imgptr[i])
				mlx_destroy_image(map_values->init, map_values->imgptr[i++]);
		}
		if (map_values->window && map_values->init)
			mlx_destroy_window(map_values->init, map_values->window);
	}
	mlx_destroy_display(map_values->init);
	if (map_values->init)
		free(map_values->init);
	if (map_values->map)
		free_doublepoint((void **)map_values->map);
	if (map_values->imgptr)
		free(map_values->imgptr);
	if (map_values->collectable)
		free(map_values->collectable);
	free(map_values);
}
