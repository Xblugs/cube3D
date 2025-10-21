/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util_pow.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:14:19 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/28 13:14:21 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int				ft_rec_expo(int nb);
int				ft_rec_expo_u(unsigned int nb);
int				ft_rec_expo_base(unsigned long nb, int base);
unsigned long	ft_iter_pow(unsigned long nb, unsigned long power);

int	ft_rec_expo(int nb)
{
	int	n;

	n = 1;
	if (nb % 10 == nb || nb == 0)
		return (1);
	n = n + ft_rec_expo(nb / 10);
	return (n);
}

int	ft_rec_expo_u(unsigned int nb)
{
	int	n;

	n = 1;
	if (nb % 10 == nb || nb == 0)
		return (1);
	n = n + ft_rec_expo_u(nb / 10);
	return (n);
}

int	ft_rec_expo_base(unsigned long nb, int base)
{
	int	n;

	n = 1;
	if (nb % base == nb || nb == 0)
		return (1);
	n = n + ft_rec_expo_base(nb / base, base);
	return (n);
}

// only use with strictly positive numbers
unsigned long	ft_iter_pow(unsigned long nb, unsigned long power)
{
	unsigned long	n;

	n = 1;
	if (power == 0)
		return (1);
	while (power > 0)
	{
		n = n * nb;
		power--;
	}
	return (n);
}
