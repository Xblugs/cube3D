/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   16_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:32:31 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:15:35 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	free_texture(t_map *config);

void	free_dbl_arr(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
		free(lines[i++]);
	free(lines);
}

void	free_config(t_map *config)
{
	free_texture(config);
	if (config->map)
		free_dbl_arr(config->map);
}

static void	free_texture(t_map *config)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		free(config->path[i]);
		config->path[i] = NULL;
		i++;
	}
}

int	free_lines_and_config(t_map *map, char **lines, int ret)
{
	if (lines)
		free_dbl_arr(lines);
	if (map)
		free_config(map);
	return (ret);
}
