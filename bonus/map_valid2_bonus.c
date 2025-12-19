/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_valid2_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 15:55:29 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/19 13:38:32 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

int	map_check_bonus(char **map, t_map *maps, int x, int y)
{
	if (map[x][y] == 'C')
	{
		if (maps->collectible)
		{
			maps->collectible[maps->collectibles].x = x;
			maps->collectible[maps->collectibles].y = y;
		}
		maps->collectibles++;
	}
	else if (map[x][y] == 'X')
	{
		if (maps->enemies)
		{
			maps->enemies[maps->enemy_count].x = x;
			maps->enemies[maps->enemy_count].y = y;
			maps->enemies[maps->enemy_count].direction = 1;
			map[x][y] = '0';
		}
		maps->enemy_count++;
	}
	else if (map[x][y] != '0' && map[x][y] != '1' && map[x][y] != '\n')
		return (1);
	return (0);
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

void	*map_valid(char **map, t_map *cpymaps)
{
	t_map	*maps;

	maps = ft_calloc(sizeof(t_map), 1);
	if (!maps || !cpymaps)
		return (NULL);
	init_maps(maps);
	if (!map_chars(map, maps))
		return (freemsg(maps, cpymaps, ""), NULL);
	if (!wall_check(map))
		return (freemsg(maps, cpymaps, NOTRECTERROR), NULL);
	if (maps->exit.count != 1 || maps->player.count != 1
		|| maps->collectibles < 1)
		return (freemsg(maps, cpymaps, WRONGCHARCOUNT), NULL);
	return (maps);
}
