/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/16 19:10:47 by cczerwin          #+#    #+#             */
/*   Updated: 2025/01/16 19:10:49 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t		ft_strlen(const char *s);
char		*ft_strchr(const char *s, int c);
char		*ft_strdup(const char *src);
char		*gnl_strjoin(char *s1, char *s2, int to_free);
void		*ft_memcpy(void *dest, const void *src, size_t n);

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	while (s[i] != 0)
		i++;
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	if ((char)c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (*s != 0)
	{
		if (*s == (char)c)
		{
			return ((char *)s);
		}
		s++;
	}
	return (0);
}

char	*ft_strdup(const char *src)
{
	char	*dup;
	size_t	i;

	dup = malloc((ft_strlen(src) + 1) * sizeof(char));
	if (dup == NULL)
		return (NULL);
	i = 0;
	while (src[i] != 0)
	{
		dup[i] = src[i];
		i++;
	}
	dup[i] = 0;
	return (dup);
}

char	*gnl_strjoin(char *s1, char *s2, int to_free)
{
	char	*join;
	size_t	len1;
	size_t	len2;

	if (s1 == 0 || s2 == 0)
		return (NULL);
	len1 = ft_strlen(s1);
	len2 = ft_strlen(s2);
	join = malloc((len1 + len2 + 1) * sizeof(char));
	if (join == NULL)
		return (NULL);
	ft_memcpy(join, s1, len1);
	ft_memcpy(&join[len1], s2, len2);
	join[len1 + len2] = 0;
	if (to_free == 1 || to_free == 3)
		free (s1);
	else if (to_free == 2 || to_free == 3)
		free (s2);
	return (join);
}

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str;
	char	*dst;

	if ((dest == NULL && src == NULL) || n == 0)
		return (dest);
	str = NULL;
	str = (char *)src;
	dst = NULL;
	dst = (char *)dest;
	i = 0;
	while (i < n)
	{
		dst[i] = str[i];
		i++;
	}
	return (dest);
}
