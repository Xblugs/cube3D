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

// instructions to do once on startup
static void	exec_init(t_data *data, t_calc *calc)
{
	precalc_val(data, calc);
	start_pos_wrapper(data, data->map, data->rc);
}

// separated to be called on hook
int	exec_loop(t_data *data)
{
	raycast_wrapper(data, data->rc);
	return (0);
}
