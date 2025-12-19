/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_game_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/01 17:51:40 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/19 13:48:32 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

void	init_maps(t_map *maps)
{
	maps->collectibles = 0;
	maps->exit.count = 0;
	maps->player.count = 0;
	maps->move_count = 0;
	maps->map_height = 0;
	maps->map_width = 0;
	maps->enemy_count = 0;
	maps->current_frame = 0;
	maps->map = NULL;
	maps->collectible = NULL;
	maps->enemies = NULL;
	maps->window = NULL;
	maps->init = NULL;
	gettimeofday(&maps->last_frame_time, NULL);
	gettimeofday(&maps->last_move_time, NULL);
}

void	xpm_control(t_map *map_values)
{
	int	i;

	if (!map_values->imgptr.exit_open || !map_values->imgptr.wall
		|| !map_values->imgptr.floor || !map_values->imgptr.exit
		|| !map_values->imgptr.collectible || !map_values->imgptr.player
		|| !map_values->imgptr.movecount_bg || !map_values->imgptr.firstline)
		(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
	i = 0;
	while (i < 5)
	{
		if (!map_values->imgptr.enemy[i])
			(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
		i++;
	}
	i = 0;
	while (i < 10)
	{
		if (!map_values->imgptr.digits[i])
			(ft_putendl_fd(TXTER, 2), free_all(map_values), exit(EXIT_FAILURE));
		i++;
	}
}

void	init_window(t_map *map_values, char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	init_images(map_values);
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
	display_move_count(map_values);
}
