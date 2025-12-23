/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   9_check_map_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:48 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 17:06:38 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	valid_char(char c)
{
	return (c == '0' || c == '1' || c == 'N' || c == 'S'
		|| c == 'W' || c == 'E' || c == ' ');
}

/*
	y loops over each line in the map_lines[y]
	x loops over each character in the line map_lines[y][x]
	checks if the character is allowed (0 1 N S E W ' ')
*/
int	check_map_chars(char **map_lines)
{
	int	y;
	int	x;

	y = 0;
	while (map_lines[y])
	{
		x = 0;
		while (map_lines[y][x])
		{
			if (!valid_char(map_lines[y][x]))
			{
				printf("%sInvalid map char: '%c' at y: %d, x: %d\n",
					ERROR, map_lines[y][x], y + 1, x + 1);
				return (0);
			}
			x++;
		}
		y++;
	}
	return (1);
}
