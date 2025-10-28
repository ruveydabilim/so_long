/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:46:32 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/28 17:22:07 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../external/mlx/mlx.h"
# include "../external/ft_printf/ft_printf.h"
# include "../external/libft/libft.h"
# include "../external/get_next_line/get_next_line.h"
# include <fcntl.h>

typedef struct s_mchar
{
	int	x;
	int	y;
	int	count;
}	t_mchar;

typedef struct s_map
{
	t_mchar	*collectable;
	t_mchar	player;
	t_mchar	exit;
	int		collectables;
}	t_map;

char	**map_parser(char *arg);
t_map	*map_validation(char **map);
void	*so_long(char **map);

#endif