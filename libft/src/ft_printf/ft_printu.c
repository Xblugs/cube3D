/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printu.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/28 13:08:33 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/28 13:08:39 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_printu(int flag, int width, int prec, unsigned int data);
static int	ft_printu_left(int flag, int width, int prec, unsigned int data);
static int	ft_printu_right(int flag, int width, int prec, unsigned int data);
static int	ft_printnbr_u(int exp, unsigned int data);

int	ft_printu(int flag, int width, int prec, unsigned int data)
{
	int	count;

	count = 0;
	if (prec == -2)
		prec = 0;
	if (prec > -1)
		flag = flag & 0b11101;
	if ((flag & 0b00001) == 1)
		count = count + ft_printu_left(flag, width, prec, data);
	if ((flag & 0b00001) == 0)
		count = count + ft_printu_right(flag, width, prec, data);
	return (count);
}

static int	ft_printu_left(int flag, int width, int prec, unsigned int data)
{
	int	count;
	int	exp;

	count = 0;
	exp = ft_rec_expo_u(data);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < prec)
		count = count + ft_padding(2, prec - exp);
	count = count + ft_printnbr_u(exp, data);
	if (exp < width && prec > exp)
		count = count + ft_padding(flag, width - prec);
	if (exp < width && prec <= exp)
		count = count + ft_padding(flag, width - exp);
	return (count);
}

static int	ft_printu_right(int flag, int width, int prec, unsigned int data)
{
	int	count;
	int	exp;

	count = 0;
	exp = ft_rec_expo_u(data);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < width && exp < prec)
		count = count + ft_padding(flag, width - prec);
	else if (exp < width && exp >= prec)
		count = count + ft_padding(flag, width - exp);
	if (exp < prec)
		count = count + ft_padding(2, prec - exp);
	count = count + ft_printnbr_u(exp, data);
	return (count);
}

static int	ft_printnbr_u(int exp, unsigned int data)
{
	int	count;
	int	n;
	int	pow;

	count = 0;
	if (exp >= 1)
	{
		while (exp > 1)
		{
			pow = ft_iter_pow(10, exp - 1);
			n = (data / pow) + '0';
			count = count + write (1, &n, 1);
			data = data - ((n - '0') * pow);
			exp--;
		}
		n = data + '0';
		count = count + write (1, &n, 1);
	}
	return (count);
}
