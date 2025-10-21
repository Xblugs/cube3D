/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 16:24:08 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/16 16:24:11 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c);

char	*ft_strrchr(const char *s, int c)
{
	size_t	i;
	int		j;

	i = 0;
	j = -1;
	if ((char)c == 0)
		return ((char *)(s + ft_strlen(s)));
	while (s[i] != 0)
	{
		if (s[i] == (char)c)
		{
			j = i;
		}
		i++;
	}
	if (j != -1)
		return ((char *)(s + j));
	return (0);
}
