/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   13_flood_prep.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:32:15 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 16:14:43 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static char	**alloc_normalized_map(int height, int width);
static void	fill_line_with_spaces(char *dest, char *source, int width);

/*
	Align map width for each line to prevent any read/write error
	in case the map isn't a rectangle or a square
*/
char	**normalize_map(char **map, int height, int width)
{
	char	**new;
	int		y;

	new = alloc_normalized_map(height, width);
	if (!new)
		return (NULL);
	y = 0;
	while (y < height)
	{
		fill_line_with_spaces(new[y], map[y], width);
		y++;
	}
	return (new);
}

/*
    makes a full rectangular copy of the map
    replaces all spaces with '1'
*/
char	**prepare_for_flood(char **map, int height, int width)
{
	char	**copy;
	int		y;
	int		x;

	copy = normalize_map(map, height, width);
	if (!copy)
		return (NULL);
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			x++;
		}
		y++;
	}
	return (copy);
}

/*
	Allocate memory for the normalized map
*/
static char	**alloc_normalized_map(int height, int width)
{
	char	**map;
	int		y;

	map = ft_calloc((height + 1), sizeof(char *));
	if (!map)
		return (NULL);
	y = 0;
	while (y < height)
	{
		map[y] = ft_calloc((width + 1), sizeof(char));
		if (!map[y])
		{
			free_dbl_arr(map);
			return (NULL);
		}
		y++;
	}
	map[y] = NULL;
	return (map);
}

/*
	Copy the map content and fill with spaces as needed
*/
static void	fill_line_with_spaces(char *dest, char *source, int width)
{
	int	x;
	int	len;

	if (source)
		len = ft_strlen(source);
	else
		len = 0;
	x = 0;
	while (x < width)
	{
		if (source && x < len && source[x])
			dest[x] = source[x];
		else
			dest[x] = ' ';
		x++;
	}
	dest[x] = '\0';
}
