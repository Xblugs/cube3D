/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_recursive_factorial.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 15:07:49 by cczerwin          #+#    #+#             */
/*   Updated: 2024/07/18 15:07:51 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_rec_factorial(int nb);

int	ft_rec_factorial(int nb)
{
	int	n;

	n = 1;
	if (nb == 0)
		return (1);
	n = nb * ft_rec_factorial(nb - 1);
	return (n);
}
