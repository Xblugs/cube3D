/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/14 17:05:31 by cczerwin          #+#    #+#             */
/*   Updated: 2024/07/14 17:05:35 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size);

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	j;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	if (dst == 0 || size == 0 || src == 0)
		return (len_src);
	i = 0;
	j = 0;
	if (size < len_dst || size == 0)
		return (len_src + size);
	while (dst[i] != 0)
		i++;
	while (src[j] != 0 && j < size - len_dst - 1 && i < size)
	{
		dst[i + j] = (char)src[j];
		j++;
	}
	dst[i + j] = 0;
	return (len_dst + len_src);
}
