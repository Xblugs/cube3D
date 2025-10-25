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
	t_calc		calc;
	t_raycast	rc;
	int			j;

	j = 0;
	rc = (t_raycast){0};
	data->rc = &rc;
	precalc_val(data, &calc);
	start_pos_wrapper(data, data->map, data->rc);
	raycast_wrapper(data, &rc);
	for (int i = 0; i < WIDTH; i++)
	{
		// made for full-screen debug in terminal, to be deleted later
		printf("(x, y) = (%d, %d)\t", rc.wall_hit[i][X], rc.wall_hit[i][Y]);
		if (i % 8 == 0)
			printf("\n");
	}
	for (int i = 0; i < WIDTH; i++)
		if (rc.wall_hit[i][X] || rc.wall_hit[i][Y])
			j++;
	printf("\n%d\n", j);
	brick_wall(data);
	mlx_loop(data->mlx);
}
