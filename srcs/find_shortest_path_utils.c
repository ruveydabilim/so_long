/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path_utils.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/19 16:40:00 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/19 16:43:43 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

int	abs_value(int n)
{
	if (n < 0)
		return (-n);
	return (n);
}

int	manhattan_distance(int x1, int y1, int x2, int y2)
{
	return (abs_value(x1 - x2) + abs_value(y1 - y2));
}

void	init_directions(int dx[4], int dy[4])
{
	dx[0] = 0;
	dx[1] = 0;
	dx[2] = 1;
	dx[3] = -1;
	dy[0] = 1;
	dy[1] = -1;
	dy[2] = 0;
	dy[3] = 0;
}

char	**copy_map(char **original_map, int height)
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
