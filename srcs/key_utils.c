/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/31 16:49:22 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/09 16:30:11 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	move_up(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x - 1][map_values->player.y] != '1')
	{
		if (map[map_values->player.x - 1][map_values->player.y] == 'C')
			map_values->collectibles--;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
		if (map[map_values->player.x - 1][map_values->player.y] == 'E'
				&& map_values->collectibles == 0)
		{
			exit_message(map_values);
			free_all(map_values);
			exit(0);
		}
		if (map[map_values->player.x][map_values->player.y]
			!= map[map_values->exit.x][map_values->exit.y])
			map[map_values->player.x][map_values->player.y] = '0';
		else
			map[map_values->player.x][map_values->player.y] = 'E';
		map[map_values->player.x - 1][map_values->player.y] = 'P';
		map_values->player.x = map_values->player.x - 1;
		update_img(map_values, 'W');
	}
}

static void	move_down(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x + 1][map_values->player.y] != '1')
	{
		if (map[map_values->player.x + 1][map_values->player.y] == 'C')
			map_values->collectibles--;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
		if (map[map_values->player.x + 1][map_values->player.y] == 'E'
			&& map_values->collectibles == 0)
		{
			exit_message(map_values);
			free_all(map_values);
			exit(0);
		}
		if (map[map_values->player.x][map_values->player.y]
			!= map[map_values->exit.x][map_values->exit.y])
			map[map_values->player.x][map_values->player.y] = '0';
		else
			map[map_values->player.x][map_values->player.y] = 'E';
		map[map_values->player.x + 1][map_values->player.y] = 'P';
		map_values->player.x = map_values->player.x + 1;
		update_img(map_values, 'S');
	}
}

static void	move_left(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x][map_values->player.y - 1] != '1')
	{
		if (map[map_values->player.x][map_values->player.y - 1] == 'C')
			map_values->collectibles--;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
		if (map[map_values->player.x][map_values->player.y - 1] == 'E'
			&& map_values->collectibles == 0)
		{
			exit_message(map_values);
			free_all(map_values);
			exit(0);
		}
		if (map[map_values->player.x][map_values->player.y]
			!= map[map_values->exit.x][map_values->exit.y])
			map[map_values->player.x][map_values->player.y] = '0';
		else
			map[map_values->player.x][map_values->player.y] = 'E';
		map[map_values->player.x][map_values->player.y - 1] = 'P';
		map_values->player.y = map_values->player.y - 1;
		update_img(map_values, 'A');
	}
}

static void	move_right(t_map *map_values)
{
	char	**map;

	map = map_values->map;
	if (map[map_values->player.x][map_values->player.y + 1] != '1')
	{
		if (map[map_values->player.x][map_values->player.y + 1] == 'C')
			map_values->collectibles--;
		map_values->move_count++;
		ft_printf("move count: %d\n", map_values->move_count);
		if (map[map_values->player.x][map_values->player.y + 1] == 'E'
			&& map_values->collectibles == 0)
		{
			exit_message(map_values);
			free_all(map_values);
			exit(0);
		}
		if (map[map_values->player.x][map_values->player.y]
			!= map[map_values->exit.x][map_values->exit.y])
			map[map_values->player.x][map_values->player.y] = '0';
		else
			map[map_values->player.x][map_values->player.y] = 'E';
		map[map_values->player.x][map_values->player.y + 1] = 'P';
		map_values->player.y = map_values->player.y + 1;
		update_img(map_values, 'D');
	}
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
	redraw_window(map_values, map_values->map);
}
