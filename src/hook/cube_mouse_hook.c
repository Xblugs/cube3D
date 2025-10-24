/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_mouse_hook.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:09:25 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/21 16:09:27 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	mouse_io(t_data *data)
{
	if (data != NULL)
		printf(CYAN"Cursor locked in!%s\n", END);
	else if (data == NULL)
		printf(PURPLE"Cursor escaped!%s\n", END);
	return (0);
}

int	mouse_handler(int mouse, int x, int y, t_data *data)
{
	if (mouse == LMB)
		printf("Cursor at (x, y) = [%d, %d]\n", x, y);
	else if (mouse == WHEEL_CLICK)
		print_pos(data);
	return (0);
}

//mlx_mouse_hide() leaks :(
/*
	else if (keycode == 'h')
			mlx_mouse_hide(data->mlx, data->win);
	else if (keycode == 'm')
			mlx_mouse_show(data->mlx, data->win);
*/