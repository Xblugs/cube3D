/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/25 13:52:02 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/25 13:52:05 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	int_cleanup(int **intmap, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		if (intmap[i] != NULL)
			free(intmap[i]);
		i++;
	}
	free(intmap);
}

void	char_cleanup(char **charmap, int line)
{
	int	i;

	i = 0;
	while (i < line)
	{
		if (charmap[i] != NULL)
			free(charmap[i]);
		i++;
	}
	free(charmap);
}
