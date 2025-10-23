/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/23 19:05:50 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/23 19:05:51 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	exec_func(t_data *data)
{
	find_start_pos(data->map);
	printf("pos(x, y) = (%d, %d)\n", data->map->pos[0], data->map->pos[1]);
	printf("   (l, c) = (%d, %d)\n\n", data->map->line, data->map->col);
	brick_wall(data);
	mlx_loop(data->mlx);
}

void	find_start_pos(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->line)
	{
		j = 0;
		while (j < map->col)
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S'
				|| map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				map->pos[0] = j;
				map->pos[1] = i;
				return ;
			}
			j++;
		}
		i++;
	}
	printf("This should never print as map is correct at this point\n");
}
