/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_debug.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/22 14:50:41 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/22 14:50:42 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	for memory alignement purposes (and ordering)
	(also for curiosity)
*/
void	size_of_struct(void)
{
	printf("sizeof(t_data\tt_img\tt_draw\tt_map\tt_tex\tt_calc\tt_raycast)\n");
	printf("\t[%lu]\t[%lu]\t[%lu]\t[%lu]\t[%lu]\t[%lu]\t[%lu]\n\n",
		sizeof(t_data), sizeof(t_img), sizeof(t_draw), sizeof(t_map),
		sizeof(t_tex), sizeof(t_calc), sizeof(t_raycast));
}

void	print_pos(t_data *data)
{
	printf(B_WHITE"Player coordinates:\n");
	printf("\tplayer is located at [%d, %d]",
		data->rc->pos[X], data->rc->pos[Y]);
	printf(", looking at [%d°]%s\n\n", data->rc->view_angle, END);
}

/*
	Every ray should ALWAYS hit since correct maps are closed
	otherwise some memory cleaning is needed between frames

	Change modulo value to display more or less rays data
*/
void	print_raycast_hit(t_raycast *rc)
{
	const int	scale = 10;
	int			i;
	int			j;

	i = 0;
	j = 0;
	printf(GREEN"\tDEBUG RAYCAST VALUES%s\n", END);
	printf(GREEN"\tPrinting 1:%d rays values%s\n", scale, END);
	while (i < WIDTH)
	{
		if (i % scale == 0)
			printf("(x, y) = (%d, %d)\n",
				rc->wall_hit[i][X], rc->wall_hit[i][Y]);
		if (rc->wall_hit[i][X] != 0 || rc->wall_hit[i][Y] != 0)
			j++;
		i++;
	}
	printf("%d raycast hit a wall out of %d casted\n", j, WIDTH);
	printf(GREEN"\tDEBUG RAYCAST END%s\n", END);
}
