/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:44:48 by rbilim            #+#    #+#             */
/*   Updated: 2025/12/14 23:58:46 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long_bonus.h"

static int	is_valid(char *arg)
{
	int	len;

	len = ft_strlen(arg);
	if (len < 4)
		return (0);
	if (arg[len - 1] == 'r' && arg[len - 2] == 'e'
		&& arg[len - 3] == 'b' && arg[len - 4] == '.'
		&& arg[len - 5] && arg[len -5] != '/')
		return (1);
	return (0);
}

static int	count_lines(char *arg)
{
	int		fd;
	int		count;
	char	*line;

	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (0);
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		count++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (count);
}

char	**map_parser(char *arg)
{
	char	**map;
	int		i;
	int		fd;
	int		lines;

	if (!arg || !*arg || !is_valid(arg))
		return (write(2, INVARGTYPE, 30), NULL);
	lines = count_lines(arg);
	if (lines == 0)
		return (write(2, INVFILE, 30), NULL);
	map = ft_calloc(sizeof(char *), (lines + 1));
	if (!map)
		return (NULL);
	fd = open(arg, O_RDONLY);
	if (fd < 0)
		return (free(map), NULL);
	i = 0;
	while (i < lines)
		map[i++] = get_next_line(fd);
	map[i] = NULL;
	close(fd);
	return (map);
}
