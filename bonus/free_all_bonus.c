/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:51:39 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/15 16:36:16 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

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

void	freemsg(void *free1, void *free2, char *message)
{
	if (free1)
		free(free1);
	if (free2)
		free(free2);
	if (message)
		ft_printf("%s\n", message);
}

void	exit_message(t_map *map_values, int is_won)
{
	if (is_won)
		ft_printf(WONGAME);
	else
		ft_printf(GAMEOVER);
	free_all(map_values);
	exit(0);
}

void	free_bonusimages(t_map *map_values)
{
	int	i;

	i = 0;
	while (i < 5)
	{
		if (map_values->imgptr.enemy[i])
			mlx_destroy_image(map_values->init, map_values->imgptr.enemy[i]);
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (map_values->imgptr.digits[i])
			mlx_destroy_image(map_values->init, map_values->imgptr.digits[i]);
		i++;
	}
}

void	free_all(t_map *map_values)
{
	if (!map_values)
		return ;
	if (map_values->init)
	{
		free_bonusimages(map_values);
		free_images(map_values);
		if (map_values->window)
			mlx_destroy_window(map_values->init, map_values->window);
		mlx_destroy_display(map_values->init);
		free(map_values->init);
	}
	if (map_values->map)
		free_doublepoint((void **)map_values->map);
	if (map_values->collectible)
		free(map_values->collectible);
	if (map_values->enemies)
		free(map_values->enemies);
	free(map_values);
}
