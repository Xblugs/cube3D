/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printdi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/24 16:45:46 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/24 16:45:51 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_printd(int flag, int width, int prec, int data);
static int	ft_printd_left(int flag, int width, int prec, int data);
static int	ft_printd_right(int flag, int width, int prec, int data);
static int	ft_printd_right2(int flag, int width, int prec, int data);
static int	ft_printnbr_d(int exp, int data);

int	ft_printd(int flag, int width, int prec, int data)
{
	int	count;

	count = 0;
	if (prec == -2)
		prec = 0;
	if (prec > -1)
		flag = flag & 0b11101;
	if (data == -2147483648)
		return (write (1, "-2147483648", 11));
	if ((flag & 0b00001) == 1)
		count = count + ft_printd_left(flag, width, prec, data);
	if ((flag & 0b00001) == 0)
		count = count + ft_printd_right(flag, width, prec, data);
	return (count);
}

static int	ft_printd_left(int flag, int width, int prec, int data)
{
	int	count;
	int	exp;
	int	sign;

	count = 0;
	sign = ft_printsign(flag, data);
	if (data < 0)
		data = -data;
	exp = ft_rec_expo(data);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < prec)
		count = count + ft_padding(2, prec - exp);
	count = count + ft_printnbr_d(exp, data);
	if (exp < width && prec > exp)
		count = count + ft_padding(flag, width - prec - sign);
	if (exp < width && prec <= exp)
		count = count + ft_padding(flag, width - exp - sign);
	return (count + sign);
}

static int	ft_printd_right(int flag, int width, int prec, int data)
{
	int	count;
	int	exp;
	int	sign;

	count = 0;
	sign = 0;
	if ((flag & 16) == 16 || (flag & 8) == 8 || data < 0)
		sign = 1;
	exp = ft_rec_expo(data);
	if (data < 0)
		exp = ft_rec_expo(-data);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < width && exp < prec)
		count = count + ft_padding(flag, width - prec - sign);
	else if (exp < width && exp >= prec && ((flag & 0b00010) != 2))
		count = count + ft_padding(flag, width - exp - sign);
	sign = ft_printsign(flag, data);
	count = count + ft_printd_right2(flag, width, prec, data);
	return (count + sign);
}

static int	ft_printd_right2(int flag, int width, int prec, int data)
{
	int	count;
	int	exp;
	int	sign;

	count = 0;
	sign = 0;
	if ((flag & 16) == 16 || (flag & 8) == 8 || data < 0)
		sign = 1;
	exp = ft_rec_expo(data);
	if (data < 0)
		exp = ft_rec_expo(-data);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < width && exp >= prec && ((flag & 0b00010) == 2))
		count = count + ft_padding(flag, width - exp - sign);
	if (exp < prec)
		count = count + ft_padding(2, prec - exp);
	if (data < 0)
		count = count + ft_printnbr_d(exp, -data);
	else
		count = count + ft_printnbr_d(exp, data);
	return (count);
}

static int	ft_printnbr_d(int exp, int data)
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
