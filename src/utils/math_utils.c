/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:45:23 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:45:25 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	deg_to_rad(double angle)
{
	return ((angle) * M_PI / 180.0);
}

double	rad_to_deg(double radian)
{
	return ((radian) * 180.0 / M_PI);
}

/*
	To be used later for potential math optimization
*/
void	precalc_val(t_data *data, t_calc *calc)
{
	*calc = (t_calc){0};
	data->calc = calc;
	calc->half_fov = FOV / 2;
	calc->half_width = WIDTH / 2;
	calc->half_height = HEIGHT / 2;
	calc->dist_to_proj = calc->half_height / tan(deg_to_rad(calc->half_fov));
	calc->angle_betweem_rays = (double)FOV / WIDTH;
	printf("Precalc values:\n");
	printf("fov/2=[%d]\tH/2=[%d]\tW/2=[%d]\tdist=[%d]\tangle=[%f]\n\n",
		calc->half_fov, calc->half_height,
		calc->half_width, calc->dist_to_proj, calc->angle_betweem_rays);
}
