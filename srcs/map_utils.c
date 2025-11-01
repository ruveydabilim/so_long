/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/01 13:47:20 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/01 13:50:32 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

void	init_maps(t_map *maps)
{
	maps->imgptr = malloc(sizeof(void *) * maps->map_height * maps->map_width);
	maps->collectable = malloc(sizeof(t_mchar *));
	maps->collectables = 0;
	maps->exit.count = 0;
	maps->player.count = 0;
	maps->move_count = 0;
}
