/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/08 12:22:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/08 18:06:26 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static char	**copy_map(char **original_map, int height)
{
	char	**map_copy;
	int		i;

	map_copy = (char **)malloc(sizeof(char *) * (height + 1));
	if (!map_copy)
		return (NULL);
	i = 0;
	while (i < height)
	{
		map_copy[i] = ft_strdup(original_map[i]);
		if (!map_copy[i])
		{
			while (--i >= 0)
				free(map_copy[i]);
			free(map_copy);
			return (NULL);
		}
		i++;
	}
	map_copy[i] = NULL;
	return (map_copy);
}

static void	find_path(char **map, int x, int y, double *count)
{
	static int	min_value;

	if (map[x][y] == 'E')
	{
		min_value = *count;
		return ;
	}
	if (map[x][y] == '1')
		return ;
	map[x][y] = '1';
	*count += 0.25;
	find_path(map, x, y + 1, count);
	find_path(map, x, y - 1, count);
	find_path(map, x + 1, y, count);
	find_path(map, x - 1, y, count);
	*count = min_value;
}

void	exit_message(t_map *map_values, int temp, int count)
{
	if (map_values->move_count - temp == count)
		ft_printf ("Congratulations! You found shortest path and escape\n");
	else
		ft_printf ("You couldn't find shortest path. You made extra %d step\n",
			count - (map_values->move_count - temp));
}

int	find_shortest_path(t_map map_values)
{
	char	**map;
	double	count;
	int		i;

	count = 0;
	map = copy_map(map_values.map, map_values.map_height);
	if (!map)
		return (0);
	find_path(map, map_values.player.x, map_values.player.y, &count);
	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
	return (count);
}
