/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/03 16:06:47 by cczerwin          #+#    #+#             */
/*   Updated: 2025/01/03 16:06:49 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_printp(int flag, int width, int prec, void *data);
static int	ft_printp_left(int flag, int width, unsigned long data);
static int	ft_printp_right(int flag, int width, unsigned long data);
static int	ft_printnbr_p(int exp, unsigned long data);

int	ft_printp(int flag, int width, int prec, void *data)
{
	int				count;
	unsigned long	addr;

	count = 0;
	if (data == NULL)
		count += ft_prints(flag, width, prec, "(nil)");
	else
	{
		addr = (unsigned long)data;
		if ((flag & 1) == 1)
			count += ft_printp_left(flag | 4, width, addr);
		else if ((flag & 1) == 0)
			count += ft_printp_right(flag | 4, width, addr);
	}
	return (count);
}

static int	ft_printp_left(int flag, int width, unsigned long data)
{
	int	count;
	int	exp;
	int	pref;

	count = 0;
	pref = ft_printpref(flag, 1);
	exp = ft_rec_expo_base(data, 16);
	count = count + ft_printnbr_p(exp, data);
	if (exp < width)
		count = count + ft_padding(flag, width - exp - pref);
	return (count + pref);
}

static int	ft_printp_right(int flag, int width, unsigned long data)
{
	int	count;
	int	exp;
	int	pref;

	count = 0;
	pref = 0;
	if ((flag & 0b000100) == 4)
		pref = 2;
	exp = ft_rec_expo_base(data, 16);
	if (exp < width)
		count = count + ft_padding(flag, width - exp - pref);
	pref = ft_printpref(flag, 1);
	count = count + ft_printnbr_p(exp, data);
	return (count + pref);
}

static int	ft_printnbr_p(int exp, unsigned long data)
{
	int				count;
	unsigned long	n;
	unsigned long	pow;

	count = 0;
	if (exp >= 1)
	{
		while (exp > 1)
		{
			pow = ft_iter_pow(16, exp - 1);
			n = (data / pow);
			count = count + write (1, &HEX_L[n], 1);
			data = data - (n * pow);
			exp--;
		}
		n = data;
		count = count + write (1, &HEX_L[n], 1);
	}
	return (count);
}
