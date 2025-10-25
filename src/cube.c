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
	TODO: Move this function to its dedicated folder/file later
*/
int	texture_init(t_data *data, t_tex *tex, t_map *map)
{
	*tex = (t_tex){0};
	data->tex = tex;
	tex->img1 = mlx_xpm_ftoi(data->mlx, map->path1, &tex->w, &tex->h);
	tex->img2 = mlx_xpm_ftoi(data->mlx, map->path2, &tex->w, &tex->h);
	tex->img3 = mlx_xpm_ftoi(data->mlx, map->path3, &tex->w, &tex->h);
	tex->img4 = mlx_xpm_ftoi(data->mlx, map->path4, &tex->w, &tex->h);
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
	t_tex	tex;

	map = (t_map){0};
	map.map = (char *[]){"1111", "1001", "10N1", "1111"};
	size_of_struct();
	data_init(data, &img, NULL);
	if (parsing_placeholder(data, &map))
		mlx_close(data);
	if (texture_init(data, &tex, &map))
		mlx_close(data);
	mlx_data_init(data);
	exec_func(data);
}

int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){0};
	if (ac == 2 && ft_strlen(av[1]) >= MIN_ARGV_LEN)
	{
		printf(B_WHITE"\n\tWIP: Check algo.md and math.md!%s\n\n", END);
		main_func(&data);
	}
	else if (ac == 2 && ft_strlen(av[1]) < MIN_ARGV_LEN)
		printf("%s", WRONG_EXT);
	else
		printf("%s", WRONG_ARGC);
	return (0);
}
