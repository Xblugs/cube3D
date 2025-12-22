/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   8_map_copy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:42 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/15 14:35:41 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

char	**map_copy(char **original_map)
{
	char	**copy_of_map;
	int		height;
	int		i;

	if (!original_map)
		return (NULL);
	height = 0;
	while (original_map[height])
		height++;
	copy_of_map = ft_calloc((height + 1), sizeof(char *));
	if (!copy_of_map)
		return (NULL);
	i = 0;
	while (i < height)
	{
		copy_of_map[i] = ft_strdup(original_map[i]);
		if (!copy_of_map[i])
		{
			free_dbl_arr(copy_of_map);
			return (NULL);
		}
		i++;
	}
	copy_of_map[i] = NULL;
	return (copy_of_map);
}
