/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_shortest_path.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/03 17:39:05 by rbilim            #+#    #+#             */
/*   Updated: 2025/11/04 17:26:14 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/so_long.h"

static void	free_visited(int **v, int h)
{
	int	i;

	if (!v)
		return ;
	i = 0;
	while (i < h)
		free(v[i++]);
	free(v);
}

static void	enqueue(t_node **head, t_mchar p, int steps)
{
	t_node	*new;
	t_node	*tmp;

	new = malloc(sizeof(t_node));
	if (!new)
		return ;
	new->pos = p;
	new->steps = steps;
	new->next = NULL;
	if (!*head)
	{
		*head = new;
		return ;
	}
	tmp = *head;
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = new;
}

static t_node	dequeue(t_node **head)
{
	t_node	node;
	t_node	*tmp;

	node = **head;
	tmp = *head;
	*head = (*head)->next;
	free(tmp);
	return (node);
}

static int	**alloc_visited(int h, int w)
{
	int	**v;
	int	i;

	v = malloc(sizeof(int *) * h);
	if (!v)
		return (NULL);
	i = -1;
	while (++i < h)
	{
		v[i] = calloc(w, sizeof(int));
		if (!v[i])
		{
			free_visited(v, i);
			return (NULL);
		}
	}
	return (v);
}

static void	process_neighbors(t_map *g, t_node node, int **v, t_node **q)
{
	static int	dirs[4][2] = {{0, -1}, {0, 1}, {-1, 0}, {1, 0}};
	int			i;
	int			nx;
	int			ny;

	i = -1;
	while (++i < 4)
	{
		nx = node.pos.x + dirs[i][0];
		ny = node.pos.y + dirs[i][1];
		if (ny >= 0 && ny < g->map_height && nx >= 0 && nx < g->map_width
			&& !v[ny][nx] && g->map[ny][nx] != '1')
		{
			v[ny][nx] = 1;
			enqueue(q, (t_mchar){nx, ny}, node.steps + 1);
		}
	}
}
/* 
static int	bfs_map(t_map *g)
{
	t_node	*q;
	int		**v;
	t_node	n;

	v = alloc_visited(g->map_height, g->map_width);
	if (!v)
		return (-1);
	q = NULL;
	enqueue(&q, g->player, 0);
	v[g->player.y][g->player.x] = 1;
	while (q)
	{
		n = dequeue(&q);
		if (n.pos.x == g->exit.x && n.pos.y == g->exit.y)
		{
			free_visited(v, g->map_height);
			return (n.steps);
		}
		process_neighbors(g, n, v, &q);
	}
	free_visited(v, g->map_height);
	return (-1);
}

int	find_shortest_path(t_map *game)
{
	int	steps;

	steps = bfs_map(game);
	if (steps == -1)
	{
		ft_printf("Error\nNo valid path to exit.\n");
		return (-1);
	}
	return (steps);
} */
// traveling salesman problem yaz.