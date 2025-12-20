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

// mlx_key_hook(data->win, &key_handler, data);
void	set_hook(t_data *data)
{
	gettimeofday(&data->t0, NULL);
	mlx_hook(data->win, ON_KEY_PRESS, KEY_PRESS, &key_handler, data);
	mlx_mouse_hook(data->win, &mouse_handler, data);
	mlx_hook(data->win, ON_ENTER, ENTER_WINDOW, &mouse_io, data);
	mlx_hook(data->win, ON_LEAVE, LEAVE_WINDOW, &mouse_io, NULL);
	mlx_hook(data->win, ON_DESTROY, NO_EVENT, &mlx_close, data);
}
