/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   7_map_prep.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:36 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:06:01 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	Ensures there's nothing after the map
*/
static int	check_lines_after_map(char **lines, int y)
{
	while (lines[y])
	{
		if (lines[y][0] != '\0')
		{
			printf("%sWrong content at line after map %d\n", ERROR, y + 1);
			return (ERR);
		}
		y++;
	}
	return (SUCCESS);
}

/*
	Scan each line to ensure only accepted character are part of the map

	Saves the maximum line lenght for later use (width)
		and number of lines (height)

	Return with [true] or [false] depending if there's content after the map
*/
int	validate_map_block(char **lines, int start, int *width, int *height)
{
	int	y;
	int	len;
	int	max_len;

	y = start;
	max_len = 0;
	*height = 0;
	while (lines[y] && is_map_line(lines[y]))
	{
		len = ft_strlen(lines[y]);
		if (len > max_len)
			max_len = len;
		(*height)++;
		y++;
	}
	*width = max_len - 1;
	return (check_lines_after_map(lines, y));
}
