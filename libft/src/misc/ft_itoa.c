/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 17:15:13 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/26 17:15:18 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char		*ft_itoa(int n);
static char	*ft_digit(char *ascii, size_t exp, int n);
int			ft_rec_expo(int nb);
static int	ft_iterative_power(int nb, int power);

char	*ft_itoa(int n)
{
	size_t	exp;
	char	*ascii;

	exp = ft_rec_expo(n);
	ascii = malloc((exp + (n < 0) + 1) * sizeof(char));
	if (ascii == NULL)
		return (NULL);
	if (n == -2147483648)
	{
		ascii = ft_memcpy(ascii, "-2147483648", 11);
		ascii[exp + 1] = 0;
		return (ascii);
	}
	return (ft_digit(ascii, exp, n));
}

static char	*ft_digit(char *ascii, size_t exp, int n)
{
	size_t	i;
	size_t	ten_pow;

	i = 0;
	if (n < 0)
	{
		ascii[0] = '-';
		n = -n;
		i++;
	}
	ten_pow = ft_iterative_power(10, exp - 1);
	while (i < (exp + (ascii[0] == '-')))
	{
		ascii[i] = n / ten_pow + '0';
		if (ten_pow >= 10)
		{
			n = n - (ascii[i] - '0') * ten_pow;
			ten_pow = ten_pow / 10;
		}
		i++;
	}
	ascii[i] = 0;
	return (ascii);
}

int	ft_rec_expo(int nb)
{
	int	n;

	n = 1;
	if (nb % 10 == nb || nb == 0)
		return (1);
	n = n + ft_rec_expo(nb / 10);
	return (n);
}

static int	ft_iterative_power(int nb, int power)
{
	int	n;

	n = 1;
	if (power < 0)
		return (0);
	if (power == 0)
		return (1);
	while (power > 0)
	{
		n = n * nb;
		power--;
	}
	return (n);
}
