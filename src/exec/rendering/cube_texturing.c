/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_texturing.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/16 18:22:19 by cczerwin          #+#    #+#             */
/*   Updated: 2025/12/16 18:22:20 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	texture_init(t_data *data, t_tex *tex, t_map *map);

/*
	Wall rendering wrapper
*/
void	draw_texture(t_data *data, t_raycast *rc, t_draw *draw)
{
	select_texture_wrapper(data, rc, draw);
}

/*
	Hardcoded textures for tests
	remove them from /texture/xpm to segfault 😉
	TODO: Move this function to its dedicated folder/file later
*/
static int	texture_init(t_data *data, t_tex *tex, t_map *map)
{
	*tex = (t_tex){0};
	data->tex = tex;
	tex->img[N] = mlx_xpm_ftoi(data->mlx, map->path[N], &tex->w, &tex->h);
	tex->img[W] = mlx_xpm_ftoi(data->mlx, map->path[W], &tex->w, &tex->h);
	tex->img[S] = mlx_xpm_ftoi(data->mlx, map->path[S], &tex->w, &tex->h);
	tex->img[E] = mlx_xpm_ftoi(data->mlx, map->path[E], &tex->w, &tex->h);
	if (!tex->img[N] || !tex->img[W] || !tex->img[S] || !tex->img[E])
	{
		printf("%s", TEXT_OPEN_FAIL);
		return (1);
	}
	return (0);
}