/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   3_parse_colors.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:05 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 16:57:49 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/*
	Checks if str only contains 0-9 and a single comma
	1. if block -> anything other than digit or comma
	2. if block -> rgb cannot start with a comma (,R,G,B)
	3. if block -> check for consecutive commas
	4. if block -> rgb cannot end with a comma ("R,G,B,")
*/
static int	valid_rgb_chars(char *line)
{
	size_t	i;

	if (!line)
		return (ERR);
	i = 0;
	while (line[i] && line[i] != '\n')
	{
		if (line[i] == ' ' || line[i] == '\t')
		{
			i++;
			continue ;
		}
		if (!ft_isdigit(line[i]) && line[i] != ',')
			return (printf("%s%s", ERROR, BAD_RGB_CHAR, STDERR_FILENO), ERR);
		if (i == 0 && line[i] == ',')
			return (printf("%s%s", ERROR,
					CANT_START_WITH_COMMA, STDERR_FILENO), ERR);
		if (line[i] == ',' && line[i + 1] == ',')
			return (printf("%s%s", ERROR,
					CONSECUTIVE_COMMAS, STDERR_FILENO), ERR);
		i++;
	}
	if (i > 0 && line[i - 1] == ',')
		return (printf("%s%s", ERROR, CANT_END_WITH_COMMA), ERR);
	return (SUCCESS);
}

/*
	Convert for exemple "200, 100, 0" 
	to an allocated int array with the values
*/
static int	*get_rgb_arr(char *line)
{
	char	**parts;
	int		*color;

	if (valid_rgb_chars(line) != SUCCESS)
		return (NULL);
	parts = ft_split(line, ',');
	if (!parts || !parts[0] || !parts[1] || !parts[2] || parts[3]
		|| parts[0][0] == '\0' || parts[1][0] == '\0' || parts[2][0] == '\0'
		|| parts[0][0] == '\n' || parts[1][0] == '\n' || parts[2][0] == '\n')
	{
		free_dbl_arr(parts);
		printf("%s%s", ERROR, BAD_RGB_FORMAT);
		return (NULL);
	}
	color = ft_calloc(3, sizeof(int));
	if (!color)
	{
		free_dbl_arr(parts);
		printf("%s%s", ERROR, ALLOC_FAIL);
		return (NULL);
	}
	color[0] = ft_atoi(parts[0]);
	color[1] = ft_atoi(parts[1]);
	color[2] = ft_atoi(parts[2]);
	return (free_dbl_arr(parts), color);
}

/*
	Verify values are between [0] and [255] only
*/
static int	valid_rgb_int(int *color)
{
	if (!color)
		return (ERR);
	if ((color[0] < 0 || color[0] > 255)
		|| (color[1] < 0 || color[1] > 255)
		|| (color[2] < 0 || color[2] > 255))
	{
		printf("%s%s", ERROR, BAD_RGB_VALUE);
		return (ERR);
	}
	return (SUCCESS);
}

/*
	Separate the values and check their validity

	"200, 100, 0" --> [200] [100] [0]
*/
int	parse_colors(char *line, short *parts_dest)
{
	int	*color;

	color = get_rgb_arr(line);
	if (!color)
	{
		printf("%s%s", ERROR, BAD_RGB_PARSE);
		return (ERR);
	}
	if (valid_rgb_int(color) != SUCCESS)
	{
		free(color);
		return (ERR);
	}
	parts_dest[0] = color[0];
	parts_dest[1] = color[1];
	parts_dest[2] = color[2];
	free(color);
	return (SUCCESS);
}

/*
	Convert RGB to hexadecimal values (int)
	hex_color = (R << 16) + (G << 8) + B
*/
int	get_rgb_hex(int r, int g, int b)
{
	int	hex_color;

	hex_color = (r << 16) + (g << 8) + b;
	return (hex_color);
}
