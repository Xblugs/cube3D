/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   17_is_text_accessible.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:33:00 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:12:09 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	is_text_accessible(t_map *map)
{
	if (!map->path[N])
		return (printf("%sNorth texture path is NULL.\n", ERROR), ERR);
	map->fd[N] = open(map->path[N], OPEN_READ);
	if (map->fd[N] == -1)
		return (printf("%sNorth texture cannot be opened.\n", ERROR), ERR);
	close(map->fd[N]);
	if (!map->path[S])
		return (printf("%sSouth texture path is NULL.\n", ERROR), ERR);
	map->fd[S] = open(map->path[S], OPEN_READ);
	if (map->fd[S] == -1)
		return (printf("%sSouth texture cannot be opened.\n", ERROR), ERR);
	close(map->fd[S]);
	if (!map->path[W])
		return (printf("%sWest texture path is NULL.\n", ERROR), ERR);
	map->fd[W] = open (map->path[W], OPEN_READ);
	if (map->fd[W] == -1)
		return (printf("%sWest texture cannot be opened.\n", ERROR), ERR);
	close(map->fd[W]);
	if (!map->path[E])
		return (printf("%sEast texture path is NULL.\n", ERROR), ERR);
	map->fd[E] = open (map->path[E], OPEN_READ);
	if (map->fd[E] == -1)
		return (printf("%sEast texture cannot be opened.\n", ERROR), ERR);
	close (map->fd[E]);
	return (SUCCESS);
}
