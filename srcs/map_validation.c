/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:10:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/09 18:49:26 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

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

static int	wall_check(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[0][i] && map[0][i] != '\n')
		if (map[0][i++] != '1')
			return (0);
	i = 0;
	while (map[i])
		i++;
	while (map[i - 1][j] && map[i - 1][j] != '\n')
		if (map[i - 1][j++] != '1')
			return (0);
	i = 1;
	if (j == 0)
		j = 1;
	while (map[i])
		if (map[i][0] != '1' || map[i++][j - 1] != '1')
			return (0);
	return (1);
}

static void	map_check(char **map, t_map *maps, int x, int y)
{
	if (map[x][y] == 'P')
	{
		maps->player.x = x;
		maps->player.y = y;
		maps->player.count++;
	}
	if (map[x][y] == 'E')
	{
		maps->exit.x = x;
		maps->exit.y = y;
		maps->exit.count++;
	}
	if (map[x][y] == 'C')
	{
		if (maps->collectible)
		{
			maps->collectible[maps->collectibles].x = x;
			maps->collectible[maps->collectibles].y = y;
		}
		maps->collectibles++;
	}
}

static t_map	*map_chars(char **map, t_map *maps, int x, int y)
{
	int		temp;

	temp = 0;
	init_maps(maps);
	while (map[x])
	{
		if (y != temp)
			return (0);
		y = 0;
		while (map[x][y])
		{
			map_check(map, maps, x, y);
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
	int		x;
	int		y;

	x = 0;
	y = 0;
	maps = ft_calloc(sizeof(t_map), 1);
	if (!maps || !cpymaps)
		return (NULL);
	if (!map_chars(map, maps, x, y) || !wall_check(map))
		return (freemsg(maps, cpymaps, "Error\nCheck map is rectangular\
 or be enclosed by walls."), NULL);
	if (maps->exit.count != 1 || maps->player.count != 1
		|| maps->collectibles < 1)
		return (freemsg(maps, cpymaps, "Error\nCheck character count"), NULL);
	maps->collectible = ft_calloc(sizeof(t_mchar), (maps->collectibles + 1));
	if (!maps->collectible)
		return (free(cpymaps), free(maps), NULL);
	floodfill(copymap, maps->player.x, maps->player.y);
	map_chars(copymap, cpymaps, x, y);
	if (cpymaps->exit.count != 0 || cpymaps->collectibles != 0)
		return (freemsg(maps, cpymaps, "Error\nMap chars not reachable"), NULL);
	maps->map = map;
	return (free_all(cpymaps), maps);
}
