/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 14:03:08 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/30 14:03:10 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void			ft_putnbr_fd(int n, int fd);
static void		ft_digit(int *nbr, int nb);
static void		ft_write(int *nbr, int fd);

void	ft_putnbr_fd(int n, int fd)
{
	int	nbr[10];

	if (n == 0)
		write (fd, "0", 1);
	if (n != 0)
	{
		if (n == -2147483648)
			write (fd, "-2147483648", 11);
		else if (n < 0)
		{
			write (fd, "-", 1);
			ft_digit(nbr, -n);
		}
		else
			ft_digit(nbr, n);
		if (n != -2147483648)
			ft_write(nbr, fd);
	}
}

void	ft_digit(int *nbr, int nb)
{
	int	div;
	int	i;

	div = 1e9;
	i = 0;
	while (i <= 9)
	{
		nbr[i] = nb / div;
		nb = nb - nbr[i] * div;
		div = div / 10;
		i++;
	}
}

void	ft_write(int *nbr, int fd)
{
	int	i;

	i = 0;
	while (nbr[i] == 0)
		i++;
	while (i <= 9)
	{
		nbr[i] = nbr[i] + '0';
		write (fd, &nbr[i], 1);
		i++;
	}
}
