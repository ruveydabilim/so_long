/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/19 14:06:37 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	update_img(t_map *map_values, int key)
{
	if (key == 'W')
		map_values->imgptr.player = map_values->imgptr.move_up;
	else if (key == 'A')
		map_values->imgptr.player = map_values->imgptr.move_left;
	else if (key == 'S')
		map_values->imgptr.player = map_values->imgptr.move_down;
	else if (key == 'D')
		map_values->imgptr.player = map_values->imgptr.player_default;
}

void	redraw_window(t_map *map_values, char **map)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	while (map[x])
	{
		y = 0;
		while (map[x][y] && map[x][y] != '\n')
		{
			control_map(map_values, map[x][y], x, y);
			y++;
		}
		x++;
	}
}
