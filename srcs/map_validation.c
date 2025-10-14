/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/14 15:10:06 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/14 18:44:55 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static	void	floodfill(char ***map, int x, int y)
{
	if ((*map[x][y]) != 1)
		(*map[x][y]) == 'P';
	else
		return ;
	floodfill(*map, x + 1, y);
	floodfill(*map, x - 1, y);
	floodfill(*map, x, y + 1);
	floodfill(*map, x, y - 1);
}

static int	wall_check(char **map)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (map[0][i])
		if (map[0][i++] != '1')
			return (0);
	i = 0;
	while (map[i])
		i++;
	while (map[i][j])
		if (map[i][j++] != 1)
			return (0);
	i = 1;
	while (map[i][j - 1])
		if (map[i][0] != '1' && map[i++][j] != '1')
			return (0);
	return (1);
}

static t_map	*map_chars(char **map, int x, int y)
{
	int		temp;
	t_map	*maps;

	temp = 0;
	while (map[x][y])
	{
		if (y != temp)
			return (0);
		y = 0;
		while (map[x][y])
		{
			if (map[x][y] == 'P')
				maps->player++;
			if (map[x][y] == 'E')
				maps->exit++;
			if (map[x][y] == 'C')
				maps->collectable++;
			if (x == 0)
				temp = y;
			y++;
		}
		x++;
	}
	return (maps);
}

int	map_validation(char **map)
{
	t_map	*maps;
	int		x;
	int		y;

	x = 0;
	y = 0;
	maps = map_chars(map, x, y);
	if (!maps)
		return (0);
	if (maps->exit != 1 || maps->player != 1 || maps->collectable < 1)
		return (0);
	if (!wall_check(map))
		return (0);
	floodfill (&map); //buraya player ın konumunu at. ve floodfill mantığını iyi kavra.
}
