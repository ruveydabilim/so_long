/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:10:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/31 17:45:54 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	void	floodfill(char **map, int x, int y)
{
	if (map[x][y] != '1')
		map[x][y] = '1';
	else
		return ;
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
		maps->collectable[maps->collectables].x = x;
		maps->collectable[maps->collectables].y = y;
		maps->collectables++;
	}
}

void	init_maps(t_map *maps)
{
	maps->collectable = malloc(sizeof(t_mchar *));
	maps->collectables = 0;
	maps->exit.count = 0;
	maps->player.count = 0;
}

static t_map	*map_chars(char **map, t_map *maps, int x, int y)
{
	int		temp;
	int		i;

	i = 0;
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
	return (maps);
}

t_map	*map_validation(char **map)
{
	t_map	*maps;
	int		x;
	int		y;

	x = 0;
	y = 0;
	maps = malloc(sizeof(t_map));
	map_chars(map, maps, x, y);
	if (!maps)
		return (0);
	if (maps->exit.count != 1 || maps->player.count != 1
		|| maps->collectables < 1)
		return (ft_printf("error! please check character count\n"), NULL);
	if (!wall_check(map))
		return (ft_printf("error! check map is rectangular\
 or be enclosed by walls.\n"), NULL);
	floodfill (map, maps->player.x, maps->player.y);
	map_chars(map, maps, x, y);
	if (maps->exit.count != 0 || maps->collectables != 0
		|| maps->collectables != 0)
		return (ft_printf("error! please check characters are reachable\n"), \
		NULL);
	return (maps);
}
