/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:46:32 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/06 13:07:37 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H
# include "../external/mlx/mlx.h"
# include "../external/ft_printf/ft_printf.h"
# include "../external/libft/libft.h"
# include "../external/get_next_line/get_next_line.h"
# include <fcntl.h>

# ifndef MAX_WIDTH
#  define MAX_WIDTH 2560
# endif

# ifndef MAX_HEIGHT
#  define MAX_HEIGHT 1440
# endif

typedef struct s_mchar
{
	int	x;
	int	y;
	int	count;
}	t_mchar;

typedef struct s_img
{
	void	*player;
	void	*collectible;
	void	*exit;
	void	*floor;
	void	*wall;
	void	*exit_open;
}	t_img;

typedef struct s_map
{
	t_mchar	*collectible;
	t_mchar	player;
	t_mchar	exit;
	t_img	imgptr;
	char	**map;
	int		map_height;
	int		map_width;
	int		collectibles;
	int		move_count;
	void	*init;
	void	*window;
}	t_map;

char	**map_parser(char *arg);
t_map	*map_validation(char **map, char **copymap, t_map *cpymaps);
void	freemsg(void *free1, void *free2, char *message);
void	*so_long(char **map, t_map *map_values);
void	press_key(t_map *map_values, int key);
void	init_maps(t_map *maps);
void	free_all(t_map *map);
void	free_doublepoint(void **ptr);
void	init_window(t_map *map_values, char **map);
void	free_images(t_map *map_values);
void	init_images(t_map *map_values);
void	redraw_window(t_map *map_values, char **map);
int		find_shortest_path(t_map *game);
void	*control_map(t_map *map_values, char map, int x, int y);
void	update_img(t_map *map_values, int key);

#endif