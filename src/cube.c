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

void	brick_wall(t_data *data)
{
	int		i;
	int		j;
	int		k;
	long	wh;

	i = 0;
	j = 0;
	k = 0;
	while (data->tex->h * j < PROJ_H)
	{
		while (data->tex->w * i < PROJ_W)
		{
			wh = int_to_long(data->tex->w * i, data->tex->h * j);
			if (i == data->img->x && j == data->img->y)
				mlx_pitow(data->mlx, data->win, data->tex->img1, wh);
			else
				brick_wall_drawing(data, wh, &k);
			k++;
			if (k == 3)
				k = 0;
			i++;
		}
		i = 0;
		j++;
	}
}

void	brick_wall_drawing(t_data *data, long wh, int *k)
{
	if (*k == 0)
		mlx_pitow(data->mlx, data->win, data->tex->img2, wh);
	else if (*k == 1)
		mlx_pitow(data->mlx, data->win, data->tex->img3, wh);
	else if (*k == 2)
		mlx_pitow(data->mlx, data->win, data->tex->img4, wh);
}

/*
	for memory alignement purposes (and ordering)
	(also for curiosity)
*/
void	size_of_struct(void)
{
	printf("sizeof(t_data\tt_img\tt_draw\tt_map\tt_tex)\n");
	printf("\t[%lu]\t[%lu]\t[%lu]\t[%lu]\t[%lu]\n", sizeof(t_data),
		sizeof(t_img), sizeof(t_draw), sizeof(t_map), sizeof(t_tex));
}

/*
	hardcoded textures for tests
	remove them from /texture/xpm to segfault 😉
*/
int	texture_init(t_data *data, t_tex *tex)
{
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

void	test_func(void)
{
	t_data	data;
	t_img	img;
	t_map	map;
	t_draw	draw;
	t_tex	tex;

	data = (t_data){0};
	img = (t_img){0};
	map = (t_map){0};
	draw = (t_draw){0};
	tex = (t_tex){0};
	size_of_struct();
	data_init(&data, &img, &draw, &map);
	if (texture_init(&data, &tex))
		mlx_close(&data);
	mlx_data_init(&data);
	brick_wall(&data);
	mlx_loop(data.mlx);
}

int	main(int ac, char **av, char **env)
{
	(void)ac;
	(void)av;
	(void)env;
	if (ac == 2)
	{
		printf("WIP: Check algo.md!\n");
		test_func();
	}
	else
		printf("%s", WRONG_ARGC);
	return (0);
}
