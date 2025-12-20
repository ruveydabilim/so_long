/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:10:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/20 10:12:30 by rbilim           ###   ########.fr       */
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
	if (map[0][0] == '\0' || map[0][0] == '\n')
		return (0);
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
	{
		if (maps->collectible)
		{
			maps->collectible[maps->collectibles].x = x;
			maps->collectible[maps->collectibles].y = y;
		}
		maps->collectibles++;
	}
	else if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != '\n')
		return (1);
	return (0);
}

static t_map	*map_chars(char **map, t_map *maps, int x, int y)
{
	int		temp;

	temp = 0;
	init_maps(maps);
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
	int		x;
	int		y;

	x = 0;
	y = 0;
	maps = ft_calloc(sizeof(t_map), 1);
	if (!maps || !cpymaps)
		return (NULL);
	if (!map_chars(map, maps, x, y))
		return (free_doubleptr(map), freemsg(maps, cpymaps, NULL), NULL);
	if (!wall_check(map))
		return (free_doubleptr(map),
			freemsg(maps, cpymaps, NOTRECTERROR), NULL);
	if (maps->exit.count != 1 || maps->player.count != 1
		|| maps->collectibles < 1)
		return (free_doubleptr(map),
			freemsg(maps, cpymaps, WRONGCHARCOUNT), NULL);
	floodfill(copymap, maps->player.x, maps->player.y);
	map_chars(copymap, cpymaps, x, y);
	if (cpymaps->exit.count != 0 || cpymaps->collectibles != 0)
		return (free_doubleptr(map),
			freemsg(maps, cpymaps, NOTPLAYABLE), NULL);
	maps->map = map;
	return (free_all(cpymaps), maps);
}
