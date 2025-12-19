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

/*
	Print on mouse [enter/exit] the screen
*/
int	mouse_io(t_data *data)
{
	if (data != NULL)
		printf(CYAN"Cursor locked in!%s\n", END);
	else if (data == NULL)
		printf(PURPLE"Cursor escaped!%s\n", END);
	return (0);
}

/*
	Interface mouse buttons to move handler wheel click to print information
*/
int	mouse_handler(int mouse, int x, int y, t_data *data)
{
	if (mouse == LMB)
		move_handler(LEFT, data);
	else if (mouse == RMB)
		move_handler(RIGHT, data);
	else if (mouse == WHEEL_UP)
		move_handler(UP, data);
	else if (mouse == WHEEL_DOWN)
		move_handler(DOWN, data);
	else if (mouse == WHEEL_CLICK)
		print_pos(data, x, y);
	return (0);
}
