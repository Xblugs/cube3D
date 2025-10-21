/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 13:21:48 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/17 13:21:51 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n);

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;
	char	*str1;
	char	*str2;

	if (n == 0 || (dest == 0 && src == 0))
		return (dest);
	str1 = NULL;
	str1 = (char *)dest;
	str2 = NULL;
	str2 = (char *)src;
	i = 0;
	while (i < n)
	{
		if (str1 < str2)
			str1[i] = str2[i];
		if (str1 > str2)
			str1[n - i - 1] = str2[n - i - 1];
		i++;
	}
	return (dest);
}
