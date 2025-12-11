/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:10:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/11 16:27:24 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static void	map_check_bonus(char **map, t_map *maps, int x, int y)
{
	if (map[x][y] == 'X')
	{
		if (maps->enemies)
		{
			maps->enemies[maps->enemy_count].x = x;
			maps->enemies[maps->enemy_count].y = y;
		}
		maps->enemy_count++;
	}
}

static t_map	*map_chars(char **map, t_map *maps, int x, int y)
{
	int		temp;

	temp = 0;
	while (map[x])
	{
		if (y != temp)
			return (0);
		y = 0;
		while (map[x][y])
		{
			map_check_bonus(map, maps, x, y);
			y++;
			if (x == 0)
				temp = y;
		}
		x++;
	}
	maps->map_height = x;
	maps->map_width = y;
	return (maps);
}

t_map	*map_validation_bonus(char **map, char **copymap, t_map *cpymaps)
{
	t_map	*maps;
	int		x;
	int		y;

	x = 0;
	y = 0;
	maps = map_validation(map, copymap, cpymaps);
	map_chars(map, maps, x, y);

}
