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

static void	print_map_data(t_map *map);

int	parsing(t_map *map, char *filename)
{
	int		fd;

	init_t_map(map);
	if (!has_right_extension(filename))
		return (printf("%sError: Wrong extension. Must be .cub\n", ERROR), 1);
	fd = open(filename, O_RDONLY);
	if (fd < 0)
		return (printf("%s%s", ERROR, OPEN_FAIL), 1);
	if ((parse_map_file(map, filename)) != 0)
		return (close(fd), printf("%sError: Parsing error.\n", ERROR), 1);
	close(fd);
	print_map_data(map);
	return (0);
}

static void	print_map_data(t_map *map)
{
	int	i;

	i = 0;
	printf("PARSING SUCCESS !\n");
	printf("\n---- TEXTURE PATHS ----\n");
	printf("North: %s\n", map->path[0]);
	printf("South: %s\n", map->path[1]);
	printf("West: %s\n", map->path[2]);
	printf("East: %s\n", map->path[3]);
	printf("\n---- FLOOR COLORS ----\n");
	printf("R = %d, G = %d, B = %d\n",
		map->floor[0], map->floor[1], map->floor[2]);
	printf("\n---- CEILING COLORS ----\n");
	printf("R = %d, G = %d, B = %d\n", map->ceiling[0],
		map->ceiling[1], map->ceiling[2]);
	printf("\n");
	while (i < map->height)
	{
		printf("%s\n", map->map[i]);
		i++;
	}
	printf("\n");
}

/*
	parsing_placeholder can be commented or deleted later on

	Init map values to {0} and associate the structures
	return 1 on error
*/
// int	parsing_placeholder(t_data *data, t_map *map)
// {
// 	int	i;

// 	i = 0;
// 	map->line = 5;
// 	map->col = ft_strlen(map->map[0]);
// 	map->path[N] = "./texture/xpm/brick.xpm";
// 	map->path[W] = "./texture/xpm/tile_cyan.xpm";
// 	map->path[S] = "./texture/xpm/tile_magenta.xpm";
// 	map->path[E] = "./texture/xpm/tile_yellow.xpm";
// 	data->map = map;
// 	printf("map =");
// 	while (i < map->line)
// 	{
// 		printf("\t%s\n", map->map[i]);
// 		i++;
// 	}
// 	printf("\n");
// 	return (0);
// }
