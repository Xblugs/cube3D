/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/17 12:58:22 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/17 12:58:23 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n);

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
