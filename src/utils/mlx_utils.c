/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 10:46:31 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 10:46:33 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	mlx_close_tex(t_data *data);

// close wrapper
int	mlx_close(t_data *data)
{
	mlx_close_tex(data);
	if (data->img->img != NULL)
		mlx_destroy_image(data->mlx, data->img->img);
	if (data->win != NULL)
		mlx_destroy_window(data->mlx, data->win);
	if (data->mlx != NULL)
	{
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map->map != NULL)
		int_cleanup(data->map->map, data->map->line);
	exit(0);
	return (0);
}

// free texture related memory
static int	mlx_close_tex(t_data *data)
{
	if (data->tex->img1 != NULL)
		mlx_destroy_image(data->mlx, data->tex->img1);
	if (data->tex->img2 != NULL)
		mlx_destroy_image(data->mlx, data->tex->img2);
	if (data->tex->img3 != NULL)
		mlx_destroy_image(data->mlx, data->tex->img3);
	if (data->tex->img4 != NULL)
		mlx_destroy_image(data->mlx, data->tex->img4);
	return (0);
}

// clear the img from data struct
void	clear_screen(t_data *data)
{
	void	*black_screen;

	black_screen = mlx_new_image(data->mlx, data->x, data->y);
	mlx_put_image_to_window(data->mlx, data->win, black_screen, 0, 0);
	mlx_put_image_to_window(data->mlx, data->win, data->img->img,
		data->pos_x, data->pos_y);
	mlx_destroy_image(data->mlx, black_screen);
}

void	int_cleanup(int **intmap, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		if (intmap[i] != NULL)
			free(intmap[i]);
		i++;
	}
	free(intmap);
}

void	char_cleanup(char **charmap, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		if (charmap[i] != NULL)
			free(charmap[i]);
		i++;
	}
	free(charmap);
}
