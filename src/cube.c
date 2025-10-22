/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:20:33 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 11:20:34 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// main

/*
	hardcoded textures for tests
	remove them from /texture/xpm to segfault 😉
*/
int	texture_init(t_data *data, t_tex *tex)
{
	*tex = (t_tex){0};
	data->tex = tex;
	tex->path1 = "./texture/xpm/brick.xpm";
	tex->path2 = "./texture/xpm/tile_cyan.xpm";
	tex->path3 = "./texture/xpm/tile_magenta.xpm";
	tex->path4 = "./texture/xpm/tile_yellow.xpm";
	tex->img1 = mlx_xpm_ftoi(data->mlx, tex->path1, &tex->w, &tex->h);
	tex->img2 = mlx_xpm_ftoi(data->mlx, tex->path2, &tex->w, &tex->h);
	tex->img3 = mlx_xpm_ftoi(data->mlx, tex->path3, &tex->w, &tex->h);
	tex->img4 = mlx_xpm_ftoi(data->mlx, tex->path4, &tex->w, &tex->h);
	if (!tex->img1 || !tex->img2 || !tex->img3 || !tex->img4)
	{
		printf("%s", TEXT_OPEN_FAIL);
		return (1);
	}
	return (0);
}

void	main_func(t_data *data)
{
	t_img	img;
	t_map	map;
	t_draw	draw;
	t_tex	tex;
	t_calc	calc;

	size_of_struct();
	data_init(data, &img, &draw, &map);
	if (parsing())
		mlx_close(data);
	precalc_val(data, &calc);
	if (texture_init(data, &tex))
		mlx_close(data);
	mlx_data_init(data);
	brick_wall(data);
	mlx_loop(data->mlx);
}

int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){0};
	(void)av;
	if (ac == 2)
	{
		printf("WIP: Check algo.md and math.md!\n");
		main_func(&data);
	}
	else
		printf("%s", WRONG_ARGC);
	return (0);
}
