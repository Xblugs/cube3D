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
// This block refuses to init map->map for reasons
// most likely requires **map to affect the *map
// *map = (t_map){0};
// map->map = (char *[]){"1111", "1001", "10N1", "1111"};
int	parsing_placeholder(t_data *data, t_map *map)
{
	map->line = 4;
	map->col = ft_strlen(map->map[0]);
	data->map = map;
	printf("map =\t%s\n\t%s\n\t%s\n\t%s\n\n",
		map->map[0], map->map[1], map->map[2], map->map[3]);
	return (0);
}
