/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_move_handler.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/24 16:48:08 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/24 16:48:09 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	forward_handler(t_data *data, t_raycast *rc);
static void	backward_handler(t_data *data, t_raycast *rc);
static void	angle_handler(int key, t_data *data);

/*
	move values depend on current orientation
	use arrow key and [wasd] for movement
*/
void	move_handler(int key, t_data *data)
{
	if (key == UP || key == 'w')
		forward_handler(data, data->rc);
	else if (key == DOWN || key == 's')
		backward_handler(data, data->rc);
	else if (key == LEFT || key == 'q' || key == RIGHT || key == 'e')
		angle_handler(key, data);
	else if (key == 'a' || key == 'd')
		lateral_handler(data, data->rc, key);
	exec_loop(data);
}

/*
	Re-using delta array to not allocate more memory

	shift is used for lateral moves
*/
void	move_prep(t_raycast *rc, int shift)
{
	rc->delta[X] = -sin(deg_to_rad(rc->view_angle + shift));
	rc->delta[Y] = +cos(deg_to_rad(rc->view_angle + shift));
	rc->delta[X] *= MOV_SPEED;
	rc->delta[Y] *= MOV_SPEED;
}

/*
	Check both directions individually
		wall licking is allowed
*/
static void	forward_handler(t_data *data, t_raycast *rc)
{
	int	x;
	int	y;

	move_prep(rc, 0);
	x = rc->pos[Y] / UNIT;
	y = (rc->pos[X] + rc->delta[X]) / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[X] += rc->delta[X];
	x = (rc->pos[Y] + rc->delta[Y]) / UNIT;
	y = rc->pos[X] / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[Y] += rc->delta[Y];
}

static void	backward_handler(t_data *data, t_raycast *rc)
{
	int	x;
	int	y;

	move_prep(rc, 0);
	x = rc->pos[Y] / UNIT;
	y = (rc->pos[X] - rc->delta[X]) / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[X] -= rc->delta[X];
	x = (rc->pos[Y] - rc->delta[Y]) / UNIT;
	y = rc->pos[X] / UNIT;
	if (data->map->map[x][y] != '1')
		rc->pos[Y] -= rc->delta[Y];
}

static void	angle_handler(int key, t_data *data)
{
	if (key == LEFT || key == 'q')
		data->rc->view_angle -= 10;
	else if (key == RIGHT || key == 'e')
		data->rc->view_angle += 10;
	if (data->rc->view_angle < 0)
		data->rc->view_angle += 360;
	else
		data->rc->view_angle %= 360;
}
