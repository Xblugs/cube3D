/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   2_parse_texture.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:30:59 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 16:50:29 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	parse_texture_path(t_map *map, char **split);

int	check_double_id(t_direction *flag, char *id)
{
	if (ft_strncmp(id, "NO", 2) == 0 && ++flag->no > 1)
		return (-1);
	if (ft_strncmp(id, "SO", 2) == 0 && ++flag->so > 1)
		return (-1);
	if (ft_strncmp(id, "WE", 2) == 0 && ++flag->we > 1)
		return (-1);
	if (ft_strncmp(id, "EA", 2) == 0 && ++flag->ea > 1)
		return (-1);
	if (ft_strncmp(id, "F", 1) == 0 && ++flag->f > 1)
		return (-1);
	if (ft_strncmp(id, "C", 1) == 0 && ++flag->c > 1)
		return (-1);
	return (0);
}

/*
	Recover RGB values
*/
static char	*join_rgb_parts_after_split(char **split)
{
	char	*res;
	char	*temp;
	int		i;

	i = 1;
	res = ft_strdup("");
	if (!res)
		return (printf("%sJoin rgb parts after split failed.\n", ERROR), NULL);
	while (split[i])
	{
		temp = ft_strjoin(res, split[i]);
		free(res);
		res = temp;
		i++;
	}
	return (res);
}

int	parse_texture_line(char *line, t_map *map)
{
	char	**split;
	int		status;
	char	*res;

	split = ft_split(line, ' ');
	if (!split || !split[0] || !split[1])
		return (free_dbl_arr(split), 0);
	status = check_double_id(&map->flags, split[0]);
	if (status == -1)
		return (free_dbl_arr(split), status);
	res = join_rgb_parts_after_split(split);
	if (!res)
		return (free_dbl_arr(split), 0);
	if (!is_color_config_line(split[0]) && parse_texture_path(map, split))
		return (free (res), free_dbl_arr(split), 1);
	else if (ft_strncmp(split[0], "F", 1) == 0
		&& parse_colors(res, map->floor) == 0)
		return (free(res), free_dbl_arr(split), 0);
	else if (ft_strncmp(split[0], "C", 1) == 0
		&& parse_colors(res, map->ceiling) == 0)
		return (free(res), free_dbl_arr(split), 0);
	else
		return (free(res), free_dbl_arr(split), -1);
	return (free(res), free_dbl_arr(split), 0);
}

/*
	Recover texture path
*/
static int	parse_texture_path(t_map *map, char **split)
{
	remove_newline(split[1]);
	if (valid_texture_path(split[1]) == ERR)
		return (free_config(map), 0);
	if (ft_strncmp(split[0], "NO", 2) == 0)
		map->path[N] = ft_strdup(split[1]);
	else if (ft_strncmp(split[0], "SO", 2) == 0)
		map->path[S] = ft_strdup(split[1]);
	else if (ft_strncmp(split[0], "WE", 2) == 0)
		map->path[W] = ft_strdup(split[1]);
	else if (ft_strncmp(split[0], "EA", 2) == 0)
		map->path[E] = ft_strdup(split[1]);
	else
		return (0);
	return (1);
}
