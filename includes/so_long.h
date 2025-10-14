/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:46:32 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/14 18:31:33 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../external/minilibx-linux/mlx.h"
# include "../external/ft_printf/ft_printf.h"
# include "../external/libft/libft.h"
# include "../external/get_next_line/get_next_line.h"
# include <fcntl.h>

typedef struct s_map
{
	int	collectable;
	int	player;
	int	exit;
}	t_map;

char	**map_parser(char *arg);
int		map_validation(char **map);

#endif