/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:44:48 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/12 23:51:56 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static int	is_valid(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (arg[len - 1] == 'r' && arg[len - 2] == 'e' 
		&& arg[len - 3] == 'b' && arg[len - 4] == '.')
			return (1);
	else
		return (0);
}

char	**map_parser(char *arg)
{
	char	*line;
	char	**map;
	int		i;
	size_t	fd;

	if (!arg || !*arg || !is_valid(arg))
		return (write(2, "error: invalid agrument type.\n", 53), NULL);
	i = 0;
	fd = open(arg, RDWR);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		map[i++] = line;
		free(line);
	}
	map[i] = NULL;
	return (map);
}
