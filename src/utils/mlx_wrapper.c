/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/18 20:20:27 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/18 20:21:01 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	function name is too long, norm unhappy
	mlx use 5 args, we need to think smart to be norm compliant
*/
void	mlx_pitow(void *mlx, void *win, void *img, long wh)
{
	int	w;
	int	h;

	w = 0;
	h = 0;
	long_to_int(wh, &w, &h);
	mlx_put_image_to_window(mlx, win, img, w, h);
}

/*
	function name is too long, norm unhappy
	just a simple wrapper to gain space
*/
void	*mlx_xpm_ftoi(void *mlx, char *file, int *width, int *height)
{
	return (mlx_xpm_file_to_image(mlx, file, width, height));
}
