/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 13:33:55 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/24 13:33:56 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char			*ft_strtrim(char const *s1, char const *set);
static int		isset(char const *s, char const *set);

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*trim;
	size_t	start;
	size_t	end;

	start = 0;
	if (s1 == 0)
	{
		trim = malloc(1 * sizeof(char));
		trim[0] = 0;
		return (trim);
	}
	while (isset(&s1[start], set))
		start++;
	end = start + ft_strlen(&s1[start]) - 1;
	while (end > start && isset(&s1[end], set))
		end--;
	trim = malloc((end - start + 2) * sizeof(char));
	if (trim == NULL)
		return (NULL);
	ft_strlcpy(trim, &s1[start], end - start + 2);
	trim[end + 1] = 0;
	return (trim);
}

static int	isset(char const *s, char const *set)
{
	char	*iset;

	if (set == NULL)
		return (1);
	iset = (char *)set;
	while (*iset != 0)
	{
		if (*iset == (char)*s)
			return (1);
		iset++;
	}
	return (0);
}
