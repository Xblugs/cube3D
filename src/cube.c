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

// map.map = (char *[]){"111", "101", "1N1", "101", "101", "101", "111"};
// map.map = (char *[]){"111111", "10E001", "111111"};
// map.map = (char *[]){"11111", "10001", "10N01", "10001", "11111"};
// map.map = (char *[]){"11111", "10001", "10101", "10N01", "11111"};
// map.map = (char *[]){"11111", "10001", "10101", "10011", "100N1", "11111"};
static void	main_func(t_data *data)
{
	t_img	img;
	t_map	map;
	t_tex	tex;

	map = (t_map){0};
	map.map = (char *[]){"11111", "10001", "10N01", "10001", "11111"};
	size_of_struct();
	data_init(data, &img, NULL);
	if (parsing_placeholder(data, &map))
		mlx_close(data);
	if (texture_init(data, &tex, &map))
		mlx_close(data);
	mlx_data_init(data);
	exec_func(data);
}

/*
	Precheck on file name to prevent unecessary calculation
*/
int	main(int ac, char **av)
{
	t_data	data;

	data = (t_data){0};
	if (ac == 2 && ft_strlen(av[1]) >= MIN_ARGV_LEN)
	{
		cube_welcome();
		main_func(&data);
	}
	else if (ac == 2 && ft_strlen(av[1]) < MIN_ARGV_LEN)
		printf("%s", WRONG_EXT);
	else
		printf("%s", WRONG_ARGC);
	return (0);
}
