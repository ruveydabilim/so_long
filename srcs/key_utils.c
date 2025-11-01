/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:49:22 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/01 14:58:45 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	move_up(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x][map_values->player.y - 1] != '1')
	{
		if (map[map_values->player.x][map_values->player.y - 1] == 'C')
			map_values->collectables--;
		if (map[map_values->player.x][map_values->player.y] != 'E')
			map[map_values->player.x][map_values->player.y] = '0';
		map[map_values->player.x][map_values->player.y - 1] = 'P';
		map_values->player.y = map_values->player.y - 1;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
	}
	map_values->map = map;
	free_doublepoint((void **)map);
}

static void	move_down(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x][map_values->player.y + 1] != '1')
	{
		if (map[map_values->player.x][map_values->player.y + 1] == 'C')
			map_values->collectables--;
		if (map[map_values->player.x][map_values->player.y] != 'E')
			map[map_values->player.x][map_values->player.y] = '0';
		map[map_values->player.x][map_values->player.y + 1] = 'P';
		map_values->player.y = map_values->player.y + 1;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
	}
	map_values->map = map;
	free_doublepoint((void **)map);
}

static void	move_left(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x - 1][map_values->player.y] != '1')
	{
		if (map[map_values->player.x - 1][map_values->player.y] == 'C')
			map_values->collectables--;
		if (map[map_values->player.x][map_values->player.y] != 'E')
			map[map_values->player.x][map_values->player.y] = '0';
		map[map_values->player.x - 1][map_values->player.y] = 'P';
		map_values->player.x = map_values->player.x - 1;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
	}
	map_values->map = map;
	free_doublepoint((void **)map);
}

static void	move_right(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x + 1][map_values->player.y] != '1')
	{
		if (map[map_values->player.x + 1][map_values->player.y] == 'C')
			map_values->collectables--;
		if (map[map_values->player.x][map_values->player.y] != 'E')
			map[map_values->player.x][map_values->player.y] = '0';
		map[map_values->player.x + 1][map_values->player.y] = 'P';
		map_values->player.x = map_values->player.x + 1;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
	}
	map_values->map = map;
	free_doublepoint((void **)map);
}

void	press_key(t_map *map_values, int key)
{
	if (key == 'A')
		move_left(map_values);
	else if (key == 'D')
		move_right(map_values);
	else if (key == 'W')
		move_up(map_values);
	else if (key == 'S')
		move_down(map_values);
	else
		return ;
}
