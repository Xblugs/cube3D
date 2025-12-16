/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   placeholder.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 17:40:12 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/22 17:40:14 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	init map values to {0} and associate the structures
	return 1 on error
*/
int	parsing_placeholder(t_data *data, t_map *map)
{
	int	i;

	i = 0;
	map->line = 5;
	map->col = ft_strlen(map->map[0]);
	map->path[N] = "./texture/xpm/brick.xpm";
	map->path[W] = "./texture/xpm/tile_cyan.xpm";
	map->path[S] = "./texture/xpm/tile_magenta.xpm";
	map->path[E] = "./texture/xpm/tile_yellow.xpm";
	data->map = map;
	printf("map =");
	while (i < map->line)
	{
		printf("\t%s\n", map->map[i]);
		i++;
	}
	printf("\n");
	return (0);
}

int	parsing(t_data *data, t_map *map);