/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:45:23 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:45:25 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

double	deg_to_rad(double angle)
{
	return ((angle) * M_PI / 180.0);
}

double	rad_to_deg(double radian)
{
	return ((radian) * 180.0 / M_PI);
}
