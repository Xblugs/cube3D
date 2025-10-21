/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_range.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/23 13:12:03 by cczerwin          #+#    #+#             */
/*   Updated: 2024/07/23 13:12:05 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	*ft_range(int min, int max);

int	*ft_range(int min, int max)
{
	int	i;
	int	*tab;

	i = 0;
	tab = NULL;
	if (min >= max)
		return (NULL);
	tab = malloc((max - min) * sizeof(int));
	while (min + i < max)
	{
		tab[i] = min + i;
		i++;
	}
	return (tab);
}
