/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:44:48 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/12 23:10:52 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

char	**map_parser(char *arg)
{
	size_t	fd;
	char	**map;
	int		i;
	char	*line;

	if (!arg || !*arg)
		return (NULL);
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
