/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   15_general_parsing.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:32:26 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:13:36 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	validate_map(t_map *config);
static int	parse_config(t_map *map, char **lines, int config_end);

/*
reads the map
find the map start
if parse error, frees all 
..
*/
int	parse_map_file(t_map *map, char *path)
{
	char	**lines;
	int		map_start;

	lines = read_map_file(path);
	if (!lines)
		return (printf("%s%s", ERROR, OPEN_FAIL), ERR);
	map_start = find_map_start(lines);
	if (map_start == -1)
		return (printf("%s%s", ERROR, NO_MAP),
			free_lines_and_config(map, lines, ERR));
	if (!parse_config(map, lines, map_start))
		return (free_lines_and_config(map, lines, ERR));
	if (is_text_accessible(map) == ERR)
		return (free_lines_and_config(map, lines, ERR));
	if (map_parsing(map, lines))
		return (free_lines_and_config(map, lines, ERR));
	free_dbl_arr(lines);
	if (!validate_map(map))
		return (free_lines_and_config(map, NULL, ERR));
	return (SUCCESS);
}

/*
reads texture path lines (NO SO WE EA F RGB C RGB)
if error returns error
checks only lines before map starts
*/
static int	parse_config(t_map *map, char **lines, int config_end)
{
	int	i;
	int	status;

	i = 0;
	while (i < config_end)
	{
		status = parse_texture_line(lines[i], map);
		if (status == -1)
		{
			printf("%sError at configuration line %d\n", ERROR, i + 1);
			return (0);
		}
		i++;
	}
	if (missing_texture_line(&map->flags))
		return (0);
	if (map->floor[0] == -1 || map->floor[1] == -1
		|| map->floor[2] == -1 || map->ceiling[0] == -1
		|| map->ceiling[1] == -1 || map->ceiling[2] == -1)
	{
		printf ("%sMissing or incomplete RGB color define.\n", ERROR);
		return (0);
	}
	return (1);
}

static int	validate_map(t_map *config)
{
	if (!check_map_chars(config->map))
		return (0);
	if (!check_if_one_spawn(config->map))
		return (0);
	else
		check_player_pos(config);
	if (!check_if_map_closed(config))
		return (0);
	return (1);
}
