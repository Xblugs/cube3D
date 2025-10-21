/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_intchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 17:25:01 by cczerwin          #+#    #+#             */
/*   Updated: 2025/03/20 17:25:03 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_intchr(int *arr, int c, int *end);

// Test up to *end INCLUDED
int	ft_intchr(int *arr, int c, int *end)
{
	if (end < arr)
		return (-1);
	while (arr != end + 1)
	{
		if (*arr == c)
		{
			return (1);
		}
		arr++;
	}
	return (0);
}
