/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 23:44:12 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/19 12:31:40 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	is_enemy_at_position(t_map *map_values, int x, int y)
{
	int	i;

	i = 0;
	while (i < map_values->enemy_count)
	{
		if (map_values->enemies[i].x == x && map_values->enemies[i].y == y)
			return (1);
		i++;
	}
	return (0);
}

static long	get_time_elapsed(struct timeval start, struct timeval current)
{
	long	elapsed;

	elapsed = (current.tv_sec - start.tv_sec) * 1000
		+ (current.tv_usec - start.tv_usec) / 1000;
	return (elapsed);
}

static void	update_animation_frame(t_map *map_values,
	struct timeval current_time, long frame_elapsed)
{
	if (frame_elapsed >= 200)
	{
		map_values->current_frame++;
		if (map_values->current_frame >= 5)
			map_values->current_frame = 0;
		map_values->last_frame_time = current_time;
	}
}

static void	update_enemy_positions(t_map *map_values,
	struct timeval current_time, long move_elapsed)
{
	if (move_elapsed >= 200)
	{
		if (map_values->enemies && map_values->enemy_count > 0)
			move_enemies(map_values);
		map_values->last_move_time = current_time;
	}
}

int	enemy_movement(t_map *map_values)
{
	struct timeval	current_time;
	long			frame_elapsed;
	long			move_elapsed;

	gettimeofday(&current_time, NULL);
	frame_elapsed = get_time_elapsed(map_values->last_frame_time, current_time);
	move_elapsed = get_time_elapsed(map_values->last_move_time, current_time);
	update_animation_frame(map_values, current_time, frame_elapsed);
	update_enemy_positions(map_values, current_time, move_elapsed);
	redraw_window(map_values);
	return (0);
}
