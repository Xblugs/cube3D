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
static long	time_since(struct timeval *t0, struct timeval *t1);

/*
	Hardcap fps to prevent re-calculating before previous render is done
		1/60 = 0.016666 second between images = ~16ms per frame
		1/50 = 0.020000 second between images = ~20ms per frame
*/
int	key_handler(int key, t_data *data)
{
	if (key == ESC)
	{
		printf(RED"ESC pressed, closing...%s\n", END);
		mlx_close(data);
	}
	if (time_since(&data->t0, &data->t1) < 16L)
		return (0);
	if (key >= 0xFF00)
		s_key_handler(key, data);
	else if (key == 'w' || key == 'a' || key == 's' || key == 'd')
		move_handler(key, data);
	else if (key == 'q' || key == 'e')
		move_handler(key, data);
	if (key != ENTER)
		printf("Key press = [%d 0x%X '%c']\n", key, key, key);
	gettimeofday(&data->t0, NULL);
	return (0);
}

/*
	Special keys start at 0xFF00 as per X11/keysymdef.h
	0xFF51 to 0xFF54 = arrow keys
*/
static int	s_key_handler(int key, t_data *data)
{
	if ((key >= 0xFF51 && key <= 0xFF54))
		move_handler(key, data);
	return (0);
}

/*
	Get a time difference between previous time t0 and current t1
		gettimeofday returns second and microseconds
*/
static long	time_since(struct timeval *t0, struct timeval *t1)
{
	gettimeofday(t1, NULL);
	return ((t1->tv_sec - t0->tv_sec) * 1000
		+ (t1->tv_usec - t0->tv_usec) / 1000);
}
