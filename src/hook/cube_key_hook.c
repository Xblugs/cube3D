/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_key_hook.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/21 16:09:18 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/21 16:09:19 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	s_key_handler(int key, t_data *data);

/*
	TODO: add gettimeofday() to limit fps output 60
	1/60 = 0.016666 second between images = ~16ms per frame
	gettimeofday returns second and microseconds

	gettimeofday(time, NULL);
	if (prev_time - time > threshold)
	{
		do something
		prev_time = time;
	}

	Add time struct into data
	--> mlx_loop_hook or hook on keypress?
*/
int	key_handler(int key, t_data *data)
{
	if (key == ESC)
	{
		printf(RED"ESC pressed, closing...%s\n", END);
		mlx_close(data);
	}
	else if (key >= 0xFF00)
		s_key_handler(key, data);
	else if (key == 'w' || key == 'a' || key == 's' || key == 'd')
		move_handler(key, data);
	if (key != ENTER)
		printf("Key press = [%d 0x%X '%c']\n", key, key, key);
	return (0);
}

/*
	Special keys start at 0xFF00 as per X11/keysymdef.h
	0xFF51 to 0xFF54 = arrow keys
*/
static int	s_key_handler(int key, t_data *data)
{
	if ((key >= 0xFF51 && key <= 0xFF54))
		(void) data;
	return (0);
}
