/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:23:50 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 11:23:51 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	Store 2 int into one long for norm dodging purposes
*/
long	int_to_long(int x, int y)
{
	return ((long)((long) x << 32) + y);
}

/*
	Retrieve 2 int from one long
*/
void	long_to_int(long l, int *x, int *y)
{
	*x = (l >> 32);
	*y = l;
}

/*
	libm math function expect radians
*/
double	deg_to_rad(double angle)
{
	return ((angle) * M_PI / 180.0);
}

double	rad_to_deg(double radian)
{
	return ((radian) * 180.0 / M_PI);
}
