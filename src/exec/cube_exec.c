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

	rc = (t_raycast){0};
	data->rc = &rc;
	precalc_val(data, &calc);
	start_pos_wrapper(data, data->map, data->rc);
	raycast_wrapper(data, &rc);
	mlx_loop(data->mlx);
}
// DEBUG PRINT FUNCTIONS
// print_raycast_hit_px(&rc);
// print_raycast_hit_index(&rc);
// print_raycast_dist(&rc);
