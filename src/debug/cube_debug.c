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

/*
	Player coordinates:
	Coordinates [x, y],	angle°
	Cursor [x, y]		Wall [x, y]
*/
void	print_pos(t_data *data, int x, int y)
{
	printf(B_WHITE"Player coordinates:\n");
	printf("\tplayer is located at [%d, %d]",
		data->rc->pos[X], data->rc->pos[Y]);
	printf(", looking at [%d°]%s\n", data->rc->view_angle, END);
	if (x != -1 && y != -1)
	{
		printf(B_WHITE"\tCursor at (x, y) = [%d, %d]\t", x, y);
		printf("Wall at (x, y) = [%d, %d]%s\n",
			data->rc->wall_hit[x][X],
			data->rc->wall_hit[x][Y], END);
	}
	printf("\n");
}

/*
	Every ray should ALWAYS hit since correct maps are closed
	otherwise some memory cleaning is needed between frames

	Change modulo value to display more or less rays data
	note: ray hit are INSIDE walls
*/
void	print_raycast_hit_px(t_raycast *rc)
{
	const int	scale = 10;
	int			count;
	int			i;

	i = 0;
	count = 0;
	printf(GREEN"\tDEBUG RAYCAST HIT VALUES%s\n", END);
	printf(GREEN"\tPrinting 1:%d rays values%s\n", scale, END);
	while (i < WIDTH)
	{
		if (i % scale == 0)
			printf("(x, y) = (%d, %d)\n",
				rc->wall_hit[i][X], rc->wall_hit[i][Y]);
		if (rc->wall_hit[i][X] != 0 || rc->wall_hit[i][Y] != 0)
			count++;
		i++;
	}
	printf("%d raycast hit a wall out of %d casted\n", count, WIDTH);
	printf(GREEN"\tDEBUG RAYCAST END%s\n", END);
}

// same function except we print index coordinates instead of px values
void	print_raycast_hit_index(t_raycast *rc)
{
	const int	scale = 10;
	int			count;
	int			i;

	i = 0;
	count = 0;
	printf(GREEN"\tDEBUG RAYCAST HIT VALUES%s\n", END);
	printf(GREEN"\tPrinting 1:%d rays values%s\n", scale, END);
	while (i < WIDTH)
	{
		if (i % scale == 0)
			printf("(x, y) = (%d, %d)\n",
				rc->wall_hit[i][X] / 64, rc->wall_hit[i][Y] / 64);
		if (rc->wall_hit[i][X] != 0 || rc->wall_hit[i][Y] != 0)
			count++;
		i++;
	}
	printf("%d raycast hit a wall out of %d casted\n", count, WIDTH);
	printf(GREEN"\tDEBUG RAYCAST END%s\n", END);
}

// prints corrected coordinates distances
void	print_raycast_dist(t_raycast *rc)
{
	const int	scale = 10;
	int			i;

	i = 0;
	printf(GREEN"\tDEBUG RAYCAST DIST VALUES%s\n", END);
	printf(GREEN"\tPrinting 1:%d rays values%s\n", scale, END);
	while (i < WIDTH)
	{
		if (i % scale == 0)
			printf("(dist) = (%d)\n", rc->wall_dist[i]);
		i++;
	}
	printf(GREEN"\tDEBUG RAYCAST END%s\n", END);
}
