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
Ensures that only empty lines exist after the map
if otherwise, error.
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
starts scanning from the starting line
checks each line to see if its a valid map
measures the len of each map line 
tracks the max line len which becomes the map's width
counts the number of consecutive map lines which becomes the map's height
updates the output parameters
after finishing the map block it calls checklinesaftermap to ensure
    no invalid or unexpected content appears after the map section
returns the result of checklinesaftermap indicatng whether
the map block is valid.

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
