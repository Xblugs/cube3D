/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/15 11:23:50 by cczerwin          #+#    #+#             */
/*   Updated: 2025/10/15 11:23:51 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// Copy pasted from ft_split: if a malloc fails, clear all
size_t	ft_splitcheck(char **split, size_t wordcount)
{
	size_t	i;
	size_t	isvalid;

	i = 0;
	isvalid = 1;
	while (i < wordcount)
	{
		if (split[i] == NULL)
			isvalid = 0;
		i++;
	}
	if (isvalid == 0)
	{
		while (i > 0)
		{
			free(split[i]);
			i--;
		}
	}
	return (isvalid);
}

// Copy pasted from ft_split + consider '\n' the same as '\0'
size_t	ft_digitcount(char const *s, char c)
{
	size_t	i;
	size_t	new_word;
	size_t	count;

	i = 0;
	new_word = 0;
	count = 0;
	while (s[i] != 0 && s[i] != '\n')
	{
		if (s[i] != c && ft_isdigit(s[i]) && new_word == 0)
			new_word = 1;
		if (s[i] == c && new_word == 1)
		{
			new_word = 0;
			count++;
		}
		i++;
	}
	if ((s[i] == 0 || s[i] == '\n') && new_word == 1)
		count++;
	return (count);
}

long	int_to_long(int x, int y)
{
	return ((long)((long) x << 32) + y);
}

void	long_to_int(long l, int *x, int *y)
{
	*x = (l >> 32);
	*y = l;
}
