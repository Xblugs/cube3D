/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_padding.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 12:28:56 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/19 12:29:04 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_padding(int flag, int n);
int	ft_printsign(int flag, int data);
int	ft_printpref(int flag, int data);

int	ft_padding(int flag, int n)
{
	int	count;

	count = 0;
	if ((flag & 0b00010) == 2)
	{
		while (n >= 1)
		{
			count = count + write (1, "0", 1);
			n--;
		}
	}
	while (n >= 1)
	{
		count = count + write (1, " ", 1);
		n--;
	}
	return (count);
}

int	ft_printsign(int flag, int data)
{
	int	count;

	count = 0;
	if (data < 0)
		count = count + write (1, "-", 1);
	else if ((flag & 0b10000) == 16)
		count = count + write (1, "+", 1);
	else if ((flag & 0b01000) == 8)
		count = count + write (1, " ", 1);
	return (count);
}

int	ft_printpref(int flag, int data)
{
	int	count;

	count = 0;
	if (data != 0)
	{
		if ((flag & 0b000100) == 4 && (flag & 0b100000) == 0)
			count = count + write (1, "0x", 2);
		else if ((flag & 0b000100) == 4 && (flag & 0b100000) == 32)
			count = count + write (1, "0X", 2);
	}
	return (count);
}
