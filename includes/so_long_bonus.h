/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long_bonus.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 20:46:32 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/15 23:35:12 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_BONUS_H
# define SO_LONG_BONUS_H
# include "../external/get_next_line/get_next_line.h"
# include "../external/ft_printf/ft_printf.h"
# include "../external/libft/libft.h"
# include "../external/mlx/mlx.h"
# include "error_messages.h"
# include "textures.h"
# include <fcntl.h>
# include <sys/time.h>

typedef struct s_mchar
{
	int	x;
	int	y;
	int	count;
	int	direction;
}	t_mchar;

typedef struct s_img
{
	void	*player;
	void	*collectible;
	void	*exit;
	void	*floor;
	void	*wall;
	void	*exit_open;
	void	*enemy[5];
	void	*digits[10];
	void	*movecount_bg;
	void	*firstline;
}	t_img;

typedef struct s_map
{
	t_mchar			*collectible;
	t_mchar			*enemies;
	t_mchar			player;
	t_mchar			exit;
	t_img			imgptr;
	char			**map;
	int				enemy_count;
	int				map_height;
	int				current_frame;
	int				frame_delay;
	int				map_width;
	int				collectibles;
	int				move_count;
	void			*init;
	void			*window;
	struct timeval	last_frame_time;
	struct timeval	last_move_time;
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
int		redraw_window(t_map *map_values);
void	*control_map(t_map *map_values, char map, int x, int y);
void	update_img(t_map *map_values, int key);
void	exit_message(t_map *map_values, int is_won);
void	xpm_control(t_map *map_values);
int		enemy_movement(t_map *map_values);
void	move_enemies(t_map *map_values);
void	display_move_count(t_map *map_values);
void	init_images(t_map *map_values);
void	free_bonusimages(t_map *map_values);
int		map_check_bonus(char **map, t_map *maps, int x, int y);
void	*map_valid(char **map, t_map *cpymaps);
t_map	*map_chars(char **map, t_map *maps);

#endif