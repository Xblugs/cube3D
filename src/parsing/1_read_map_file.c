/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   1_read_map_file.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:30:51 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/15 17:51:56 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// +2  = newline + null
static char	**add_line(char **lines, char *new_line, int count)
{
	char	**new;
	int		i;

	new = ft_calloc(count + 2, sizeof(char *));
	if (!new)
		return (NULL);
	i = 0;
	while (i < count)
	{
		new[i] = lines[i];
		i++;
	}
	new[i++] = new_line;
	new[i] = NULL;
	free(lines);
	return (new);
}

char	**read_map_file(char *filename)
{
	int		fd;
	char	*line;
	char	**lines;
	int		count;

	fd = open(filename, OPEN_READ);
	if (fd < 0)
		return (NULL);
	lines = NULL;
	count = 0;
	line = get_next_line(fd);
	while (line)
	{
		lines = add_line(lines, line, count);
		if (!lines)
			return (NULL);
		count++;
		line = get_next_line(fd);
	}
	close(fd);
	return (lines);
}

int	has_right_extension(char *filename)
{
	char	*last_four_char;

	if (!filename || ft_strlen(filename) < 4)
		return (1);
	last_four_char = filename + ft_strlen(filename) - 4;
	if (ft_strncmp(last_four_char, ".cub", 4))
		return (0);
	return (1);
}
