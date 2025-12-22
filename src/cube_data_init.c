/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_data_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:50:16 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:50:17 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	data_value_init(t_data *data, t_img *img);

/*
	Start mlx and init structure member if provided
*/
void	data_init(t_data *data, t_img *img)
{
	data->mlx = mlx_init();
	if (!data->mlx)
	{
		printf("%s", MLX_FAIL);
		exit(1);
	}
	data_value_init(data, img);
}

static void	data_value_init(t_data *data, t_img *img)
{
	if (data != NULL)
		data->img = img;
	if (img != NULL)
		*img = (t_img){0};
}

/*
	Hardcoded textures for tests
	remove them from /texture/xpm to segfault 😉
	TODO: Take a look here again once merged with parsing
*/
int	texture_init(t_data *data, t_tex *tex, t_map *map)
{
	*tex = (t_tex){0};
	data->tex = tex;
	tex->img[N] = mlx_xpm_ftoi(data->mlx, map->path[N], &tex->w[N], &tex->h[N]);
	tex->img[W] = mlx_xpm_ftoi(data->mlx, map->path[W], &tex->w[W], &tex->h[W]);
	tex->img[S] = mlx_xpm_ftoi(data->mlx, map->path[S], &tex->w[S], &tex->h[S]);
	tex->img[E] = mlx_xpm_ftoi(data->mlx, map->path[E], &tex->w[E], &tex->h[E]);
	if (!tex->img[N] || !tex->img[W] || !tex->img[S] || !tex->img[E])
	{
		printf("%s", TEXT_OPEN_FAIL);
		return (1);
	}
	return (0);
}

/*
	mlx window is initialized separately to allow for various checks
	without having to open/close any window in case something goes wrong
*/
void	mlx_data_init(t_data *data)
{
	data->win = mlx_new_window(data->mlx, WIDTH, HEIGHT, "cube3D");
	data->img->img = mlx_new_image(data->mlx, WIDTH, HEIGHT);
	if (data->img->img)
		data->img->addr = mlx_get_data_addr(data->img->img, &(data->img->bpp),
				&(data->img->line_len), &(data->img->endian));
	if (data->mlx == NULL || data->win == NULL || data->img->img == NULL)
		mlx_close(data);
	set_hook(data);
}
