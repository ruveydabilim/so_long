/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:22:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/19 17:05:06 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	check_neighbor(t_path_data *data, int *best, int next[2], int d[2])
{
	int	dist;

	if (data->map[data->curr.x + d[0]][data->curr.y + d[1]] != '1')
	{
		dist = manhattan_distance(data->curr.x + d[0], data->curr.y + d[1],
				data->exit.x, data->exit.y);
		if (dist < *best)
		{
			*best = dist;
			next[0] = data->curr.x + d[0];
			next[1] = data->curr.y + d[1];
		}
	}
}

static int	find_best_move(t_path_data *data, int next[2])
{
	int	best_dist;
	int	dx[4];
	int	dy[4];
	int	i;
	int	d[2];

	init_directions(dx, dy);
	best_dist = 2147483647;
	next[0] = data->curr.x;
	next[1] = data->curr.y;
	i = -1;
	while (++i < 4)
	{
		d[0] = dx[i];
		d[1] = dy[i];
		check_neighbor(data, &best_dist, next, d);
	}
	return (next[0] == data->curr.x && next[1] == data->curr.y);
}

static int	find_greedy_path(t_path_data *data)
{
	int	next[2];

	data->steps = 0;
	while (data->curr.x != data->exit.x || data->curr.y != data->exit.y)
	{
		if (find_best_move(data, next))
			return (0);
		if (data->map[data->curr.x][data->curr.y] != 'P'
			&& data->map[data->curr.x][data->curr.y] != 'E')
			data->map[data->curr.x][data->curr.y] = '1';
		data->curr.x = next[0];
		data->curr.y = next[1];
		data->steps++;
		if (data->steps > 10000)
			return (0);
	}
	return (data->steps);
}

void	exit_message(t_map *map_values, int temp, int count)
{
	int	moves_made;

	moves_made = map_values->move_count - temp;
	if (moves_made == count)
		ft_printf("Congratulations! You found shortest path and escape\n");
	else
		ft_printf("You couldn't find shortest path. You made extra %d step\n",
			moves_made - count);
}

int	find_shortest_path(t_map map_values)
{
	t_path_data	data;
	int			i;

	data.map = copy_map(map_values.map, map_values.map_height);
	if (!data.map)
		return (0);
	data.curr.x = map_values.player.x;
	data.curr.y = map_values.player.y;
	data.exit.x = map_values.exit.x;
	data.exit.y = map_values.exit.y;
	data.steps = find_greedy_path(&data);
	i = 0;
	while (data.map[i])
	{
		free(data.map[i]);
		i++;
	}
	return (free(data.map), data.steps);
}
