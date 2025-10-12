/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbilim <rbilim@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/12 22:23:10 by rbilim            #+#    #+#             */
/*   Updated: 2025/10/12 23:26:24 by rbilim           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "so_long.h"

int main(int argc, char **argv)
{
	char	**map;
	if (argc != 2)
		return(ft_printf("error! invalid arguman count."), 1);
	map = map_parser(argv[1]);
	
}