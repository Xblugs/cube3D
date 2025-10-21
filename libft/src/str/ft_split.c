/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:09:14 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/26 15:09:16 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			**ft_split(char const *s, char c);
static	void		ft_subsplit(char const *s, char c, char **split);
static	size_t	ft_splitcheck(char **split, size_t	wordcount);
static	size_t	ft_strcount(char const *s, char c);

char	**ft_split(char const *s, char c)
{
	size_t	j;
	char	**split;

	j = ft_strcount(s, c);
	split = malloc((j + 1) * sizeof(char *));
	if (split == NULL)
		return (NULL);
	ft_subsplit(s, c, split);
	if (ft_splitcheck(split, j) == 0)
	{
		free(split[0]);
		free(split);
		return (NULL);
	}
	return (split);
}

static	void	ft_subsplit(char const *s, char c, char **split)
{
	size_t	i;
	size_t	j;
	size_t	start;
	size_t	new_word;

	i = -1;
	j = -1;
	start = 0;
	new_word = 0;
	while (s[++i] != 0)
	{
		if (s[i] == c && new_word == 0)
			start = i + 1;
		if (s[i] == c && new_word == 1)
		{
			split[++j] = ft_substr(s, start, i - start);
			start = i + 1;
			new_word = 0;
		}
		if (s[i] != c && new_word == 0)
			new_word = 1;
	}
	if (s[i] == 0 && new_word == 1)
		split[++j] = ft_substr(s, start, i - start);
	split[++j] = 0;
}

static	size_t	ft_splitcheck(char **split, size_t	wordcount)
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

static	size_t	ft_strcount(char const *s, char c)
{
	size_t	i;
	size_t	new_word;
	size_t	count;

	i = 0;
	new_word = 0;
	count = 0;
	while (s[i] != 0)
	{
		if (s[i] != c && new_word == 0)
			new_word = 1;
		if (s[i] == c && new_word == 1)
		{
			new_word = 0;
			count++;
		}
		i++;
	}
	if (s[i] == 0 && new_word == 1)
		count++;
	return (count);
}
