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

static void	exec_init(t_data *data, t_calc *calc);
static void	precalc_val(t_data *data, t_calc *calc);

/*
	Exec wrapper
*/
void	exec_func(t_data *data)
{
	t_calc		calc;
	t_raycast	rc;

	rc = (t_raycast){0};
	data->rc = &rc;
	exec_init(data, &calc);
	exec_loop(data);
	mlx_loop(data->mlx);
}
// DEBUG PRINT FUNCTIONS
// print_raycast_hit_px(&rc);
// print_raycast_hit_index(&rc);
// print_raycast_dist(&rc);

/*
	Exec init
*/
static void	exec_init(t_data *data, t_calc *calc)
{
	precalc_val(data, calc);
	start_pos_wrapper(data, data->map, data->rc);
}

/*
	Precalculate constant values
*/
static void	precalc_val(t_data *data, t_calc *calc)
{
	*calc = (t_calc){0};
	data->calc = calc;
	calc->half_fov = FOV / 2;
	calc->half_width = WIDTH / 2;
	calc->half_height = HEIGHT / 2;
	calc->max_width = data->map->width * UNIT;
	calc->max_height = data->map->height * UNIT;
	calc->dist_to_proj = calc->half_height / tan(deg_to_rad(calc->half_fov));
	calc->angle_between_rays = (double)FOV / WIDTH;
	printf("Precalc values:\n");
	printf("fov/2=[%d]\tW/2=[%d]\tH/2=[%d]\tdist=[%d]\tangle=[%f]\n\n",
		calc->half_fov, calc->half_width,
		calc->half_height, calc->dist_to_proj, calc->angle_between_rays);
	printf("Projection bounds:\n");
	printf("width=[%d]\theight=[%d]\n\n", calc->max_width, calc->max_height);
}

/*
	Separated to be called on hook for redrawing
*/
int	exec_loop(t_data *data)
{
	raycast_wrapper(data, data->rc);
	return (0);
}
