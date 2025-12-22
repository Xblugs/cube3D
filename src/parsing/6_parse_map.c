/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   6_parse_map.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:26 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:05:27 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
si strchr trouve \n a la fin de la ligne, il le remplace
par \0
toutes les tabulations sont remplace par des ' '
pour faciliter l'alignement de map.
*/
static void	remove_map_newline(char **lines)
{
	int		i;
	int		j;
	char	*temp;

	i = 0;
	while (lines[i])
	{
		temp = ft_strchr(lines[i], '\n');
		if (temp)
			*temp = '\0';
		j = 0;
		while (lines[i][j])
		{
			if (lines[i][j] == '\t')
				lines[i][j] = ' ';
			j++;
		}
		++i;
	}
}

int	find_map_start(char **lines)
{
	int	i;

	i = 0;
	while (lines[i])
	{
		if (lines[i][0] != '\0' && !is_config_line(lines[i])
			&& is_map_line(lines[i]))
			return (i);
		i++;
	}
	return (-1);
}

/*

map lines are extracted from the .cub
a newly allocated arr of str containing only the map
lines or null if failure

*/
char	**extract_map(char **lines, int start, int line_num)
{
	char	**map;
	int		i;
	int		y;

	map = ft_calloc((line_num + 1), sizeof(char *));
	if (!map)
		return (NULL);
	i = 0;
	y = start;
	while (lines[y] && i < line_num)
	{
		if (is_map_line(lines[y]))
			map[i++] = ft_strdup(lines[y]);
		y++;
	}
	map[i] = NULL;
	return (map);
}
/*
	finds where the map starts
	
	using validate_map_block, it checks whether the map area has the
	correct shape and retrieves the map's width and height.
	
	it copies the map lines into a separate 2d array using extract_map
	
	it cleans \n  with remove_map_newline
	
	stores the map in the config
	
	it verifies that the map only contains allowed chars via check_map_chars()
	
	it ensures the map is closed
*/

int	map_parsing(t_map *config, char **lines)
{
	char	**map;
	int		start;

	start = find_map_start(lines);
	if (start == -1)
	{
		printf("%s%s", ERROR, NO_MAP);
		return (ERR);
	}
	if (validate_map_block(lines, start, &config->width,
			&config->height) == ERR)
		return (ERR);
	map = extract_map(lines, start, config->height);
	if (!map)
	{
		printf("%s%s", ERROR, ALLOC_FAIL);
		return (ERR);
	}
	remove_map_newline(map);
	config->map = map;
	if (!check_map_chars(map))
		return (ERR);
	if (!check_if_map_closed(config))
		return (ERR);
	return (SUCCESS);
}
