/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/15 12:07:01 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/17 11:35:18 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

long			ft_long_atoi(const char *nptr);
static long		ft_digit_to_long(char *digit, int min);
static int		ft_get_digit(char *digit, char *str);
static void		ft_get_digit2(char *digit, char *str);

long	ft_long_atoi(const char *nptr)
{
	char	digit[19];
	int		i;

	i = 0;
	while (i <= 18)
	{
		digit[i] = 0;
		i++;
	}
	return (ft_digit_to_long(digit, ft_get_digit(digit, (char *)nptr)));
}

static int	ft_get_digit(char *digit, char *str)
{
	int	i;
	int	min;

	i = 0;
	min = 0;
	while ((str[i] == 32 || (str[i] >= 9 && str[i] <= 13)) && str[i] != 0)
		i++;
	if ((str[i] == '+' || str[i] == '-') && str[i] != 0)
	{
		if (str[i] == '-')
			min++;
		i++;
	}
	ft_get_digit2(digit, &str[i]);
	return (min);
}

static void	ft_get_digit2(char *digit, char *str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((str[i + j] >= '0' && str[i + j] <= '9') && str[i + j] != 0)
	{
		if (str[i + j] == '0' && digit[0] == 0)
			i++;
		else
		{
			digit[j] = str[i + j];
			j++;
		}
	}
}

static long	ft_digit_to_long(char *digit, int min)
{
	long	nbr;
	int		i;

	nbr = 0;
	i = 0;
	while (digit[i] != 0)
	{
		if (i == 0)
			nbr = -digit[i] + '0';
		else
			nbr = nbr * 10 - digit[i] + '0';
		i++;
	}
	if (min % 2 == 1)
		return (nbr);
	return (-nbr);
}
