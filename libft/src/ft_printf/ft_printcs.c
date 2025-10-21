/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printcs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 13:21:02 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/19 13:21:04 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int			ft_printc(int flag, int width, int data);
int			ft_prints(int flag, int width, int prec, char *sdata);
static int	ft_prints_left(int width, int prec, char *sdata);
static int	ft_prints_right(int width, int prec, char *sdata);
static int	ft_prints_null(int flag, int width, int prec);

int	ft_printc(int flag, int width, int data)
{
	int	count;

	count = 0;
	if ((flag & 0b00001) == 1)
		count = count + write (1, &data, 1);
	count = count + ft_padding(0, width - 1);
	if ((flag & 0b00001) == 0)
		count = count + write (1, &data, 1);
	return (count);
}

int	ft_prints(int flag, int width, int prec, char *sdata)
{
	int	count;

	count = 0;
	if (prec == -2)
		prec = 0;
	if (sdata == NULL)
	{
		count = count + ft_prints_null(flag, width, prec);
		return (count);
	}
	if ((flag & 0b00001) == 1)
		count = count + ft_prints_left(width, prec, sdata);
	if ((flag & 0b00001) == 0)
		count = count + ft_prints_right(width, prec, sdata);
	return (count);
}

static int	ft_prints_left(int width, int prec, char *sdata)
{
	int	count;
	int	n;
	int	len;

	count = 0;
	n = ft_int_strlen(sdata);
	len = ft_int_strlen(sdata);
	if (prec > -1)
		n = prec;
	if (prec > -1 && prec <= len)
		count = count + write (1, &sdata[0], prec);
	else
		count = count + write (1, &sdata[0], len);
	if (len < width || len > prec || n == 0)
	{
		if (width > len)
			count = count + ft_padding(0, width - len);
		count = count + ft_padding(0, width - count);
	}
	return (count);
}

static int	ft_prints_right(int width, int prec, char *sdata)
{
	int	count;
	int	n;
	int	len;

	count = 0;
	n = ft_int_strlen(sdata);
	len = ft_int_strlen(sdata);
	if (prec > -1)
		n = prec;
	if (len < width || len > prec || n == 0)
	{
		if (width > len)
			count = count + ft_padding(0, width - len);
		count = count + ft_padding(0, width - n - count);
	}
	if (prec > -1 && prec <= len)
		count = count + write (1, &sdata[0], prec);
	else
		count = count + write (1, &sdata[0], len);
	return (count);
}

static int	ft_prints_null(int flag, int width, int prec)
{
	int	count;

	count = 0;
	if ((flag & 0b00001) == 1)
	{
		if (prec >= 6 || prec == -1)
			count = count + write (1, "(null)", 6);
		count = count + ft_padding(0, width - count);
	}
	if ((flag & 0b00001) == 0)
	{
		if (prec < 6 && prec != -1)
			count = count + ft_padding(0, width);
		else if (prec >= 6 || prec == -1)
		{
			count = count + ft_padding(0, width - 6);
			count = count + write (1, "(null)", 6);
		}
	}
	return (count);
}
