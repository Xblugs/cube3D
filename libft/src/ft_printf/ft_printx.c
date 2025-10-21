/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printx.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 17:40:12 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/19 17:40:14 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_printx(int flag, int width, int prec, unsigned int data);
static int	ft_printx_left(int flag, int width, int prec, unsigned int data);
static int	ft_printx_right(int flag, int width, int prec, unsigned int data);
static int	ft_printnbr_x(int flag, int exp, unsigned int data);

int	ft_printx(int flag, int width, int prec, unsigned int data)
{
	int	count;

	count = 0;
	if (prec == -2)
		prec = 0;
	if (prec > -1)
		flag = flag & 0b111101;
	if ((flag & 0b000001) == 1)
		count = count + ft_printx_left(flag, width, prec, data);
	if ((flag & 0b000001) == 0)
		count = count + ft_printx_right(flag, width, prec, data);
	return (count);
}

static int	ft_printx_left(int flag, int width, int prec, unsigned int data)
{
	int	count;
	int	exp;
	int	pref;

	count = 0;
	pref = ft_printpref(flag, data);
	exp = ft_rec_expo_base(data, 16);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < prec)
		count = count + ft_padding(2, prec - exp);
	count = count + ft_printnbr_x(flag, exp, data);
	if (exp < width && prec > exp)
		count = count + ft_padding(flag, width - prec - pref);
	if (exp < width && prec <= exp)
		count = count + ft_padding(flag, width - exp - pref);
	return (count + pref);
}

static int	ft_printx_right(int flag, int width, int prec, unsigned int data)
{
	int	count;
	int	exp;
	int	pref;

	count = 0;
	pref = 0;
	if ((flag & 0b000100) == 4)
		pref = 2;
	exp = ft_rec_expo_base(data, 16);
	if (data == 0 && prec == 0)
		exp--;
	if (exp < width && exp < prec)
		count = count + ft_padding(flag, width - prec - pref);
	else if (exp < width && exp >= prec && ((flag & 0b00010) != 2))
		count = count + ft_padding(flag, width - exp - pref);
	pref = ft_printpref(flag, data);
	if (exp < width && exp >= prec && ((flag & 0b00010) == 2))
		count = count + ft_padding(flag, width - exp - pref);
	if (exp < prec)
		count = count + ft_padding(2, prec - exp);
	count = count + ft_printnbr_x(flag, exp, data);
	return (count + pref);
}

static int	ft_printnbr_x(int flag, int exp, unsigned int data)
{
	int	count;
	int	n;
	int	pow;

	count = 0;
	if (exp >= 1)
	{
		while (exp > 1)
		{
			pow = ft_iter_pow(16, exp - 1);
			n = (data / pow);
			if ((flag & 0b100000) == 32)
				count = count + write (1, &HEX_U[n], 1);
			if ((flag & 0b100000) == 0)
				count = count + write (1, &HEX_L[n], 1);
			data = data - (n * pow);
			exp--;
		}
		n = data;
		if ((flag & 0b100000) == 32)
			count = count + write (1, &HEX_U[n], 1);
		if ((flag & 0b100000) == 0)
			count = count + write (1, &HEX_L[n], 1);
	}
	return (count);
}
