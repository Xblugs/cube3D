/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 16:34:33 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/17 11:21:38 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len);

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (ft_strlen(big) < ft_strlen(little) || len < ft_strlen(little))
		return (NULL);
	if (little[0] == 0)
		return ((char *)big);
	while (big[i] != 0 && i < len)
	{
		if (big[i] == little[j])
		{
			while (big[i + j] == little[j] && little[j] != 0 && i + j < len)
			{
				j++;
				if (little[j] == 0)
					return ((char *)big + i);
			}
			j = 0;
		}
		i++;
	}
	return (0);
}
