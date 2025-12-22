/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   14_init_parsing.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:32:21 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/15 16:26:56 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	init_direct_flags(t_direction *flags)
{
	flags->no = 0;
	flags->so = 0;
	flags->we = 0;
	flags->ea = 0;
	flags->f = 0;
	flags->c = 0;
}
/*
initializes rgb values to be parsed
*/

static void	init_rgb(t_map *color)
{
	color->floor[R] = -1;
	color->floor[G] = -1;
	color->floor[B] = -1;
	color->ceiling[R] = -1;
	color->ceiling[G] = -1;
	color->ceiling[B] = -1;
}

void	init_text_fd(t_map *config)
{
	config->fd[N] = -1;
	config->fd[S] = -1;
	config->fd[W] = -1;
	config->fd[E] = -1;
}

void	init_t_map(t_map *map)
{
	map->path[N] = NULL;
	map->path[S] = NULL;
	map->path[W] = NULL;
	map->path[E] = NULL;
	map->map = NULL;
	map->copy = NULL;
	map->line = 0;
	map->col = 0;
	map->height = 0;
	map->width = 0;
	init_direct_flags(&map->flags);
	init_rgb(map);
	init_text_fd(map);
}
