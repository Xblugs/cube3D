/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: morgane <git@morgane.dev>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/01 12:24:45 by morgane           #+#    #+#             */
/*   Updated: 2025/09/01 12:25:23 by morgane          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_isset(char const *s, char const *set)
{
	char	*iset;

	if (set == NULL)
		return (0);
	iset = (char *)set;
	while (*iset != 0)
	{
		if (*iset == (char)*s)
			return (1);
		iset++;
	}
	return (0);
}
