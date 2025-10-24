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
	start_pos_wrapper(data, data->map);
	brick_wall(data);
	mlx_loop(data->mlx);
}
