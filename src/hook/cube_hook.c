/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_hook.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:48:44 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:48:45 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	set_hook(t_data *data)
{
	mlx_key_hook(data->win, &key_handler, data);
	mlx_hook(data->win, ON_ENTER, 1L << 4, &mouse_io, data);
	mlx_hook(data->win, ON_LEAVE, 1L << 5, &mouse_io, NULL);
	mlx_hook(data->win, ON_DESTROY, 0L, &mlx_close, data);
	mlx_mouse_hook(data->win, &mouse_handler, data);
}
