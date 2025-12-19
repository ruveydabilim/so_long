/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:10:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/19 18:59:32 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static	void	floodfill(char **map, int x, int y)
{
	if (!map || !map[x] || !map[x][y])
		return ;
	if (map[x][y] == '1')
		return ;
	map[x][y] = '1';
	floodfill(map, x + 1, y);
	floodfill(map, x - 1, y);
	floodfill(map, x, y + 1);
	floodfill(map, x, y - 1);
}

static int	map_check(char **map, t_map *maps, int x, int y)
{
	if (map[x][y] == 'P')
	{
		maps->player.x = x;
		maps->player.y = y;
		maps->player.count++;
	}
	else if (map[x][y] == 'E')
	{
		maps->exit.x = x;
		maps->exit.y = y;
		maps->exit.count++;
	}
	else if (map[x][y] == 'C')
		map_check_bonus(map, maps, x, y);
	else if (map[x][y] == 'X')
		map_check_bonus(map, maps, x, y);
	else if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != '\n')
		return (1);
	return (0);
}

t_map	*map_chars(char **map, t_map *maps)
{
	int		temp;
	int		x;
	int		y;

	x = 0;
	y = 0;
	temp = 0;
	while (map[x])
	{
		if (y != temp && temp != 0)
			return (ft_putendl_fd(NOTRECTERROR, 2), NULL);
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			if (map_check(map, maps, x, y))
				return (ft_putendl_fd(INVCHAR, 2), NULL);
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

t_map	*map_validation(char **map, char **copymap, t_map *cpymaps)
{
	t_map	*maps;

	maps = map_valid(map, cpymaps);
	if (maps->enemy_count > 0)
	{
		maps->enemies = ft_calloc(sizeof(t_mchar), (maps->enemy_count + 1));
		if (!maps->enemies)
			return (free(cpymaps), free(maps), NULL);
	}
	maps->collectibles = 0;
	maps->enemy_count = 0;
	map_chars(map, maps);
	floodfill(copymap, maps->player.x, maps->player.y);
	map_chars(copymap, cpymaps);
	if (cpymaps->exit.count != 0 || cpymaps->collectibles != 0)
		return (free(maps->enemies), freemsg(maps, cpymaps, NOTPLAYABLE), NULL);
	maps->map = map;
	return (free_all(cpymaps), maps);
}
