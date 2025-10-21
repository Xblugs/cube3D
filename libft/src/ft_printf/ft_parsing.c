/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/19 14:34:11 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/19 14:34:14 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

int	ft_printinit(const char *str, t_param *p, va_list args);
int	ft_printflag(const char *str, int *flag);
int	ft_printwidth(const char *str, int *width, va_list args);
int	ft_printprec(const char *str, int *prec, va_list args);
int	ft_printtype(const char *str, t_param p, va_list args);

int	ft_printinit(const char *str, t_param *p, va_list args)
{
	int	i;

	i = 1;
	p->flag = 0;
	p->width = -1;
	p->prec = -1;
	i = i + ft_printflag(&str[i], &(p->flag));
	i = i + ft_printwidth(&str[i], &(p->width), args);
	i = i + ft_printprec(&str[i], &(p->prec), args);
	return (i);
}

int	ft_printflag(const char *str, int *flag)
{
	const char	flag_ok[6] = {'-', '0', '#', ' ', '+', 0};
	int			i;

	i = 0;
	while (ft_isset(&str[i], flag_ok))
	{
		if (str[i] == '-')
			*flag = *flag | 1;
		else if (str[i] == '0')
			*flag = *flag | 2;
		else if (str[i] == '#')
			*flag = *flag | 4;
		else if (str[i] == ' ')
			*flag = *flag | 8;
		else if (str[i] == '+')
			*flag = *flag | 16;
		i++;
	}
	return (i);
}

int	ft_printwidth(const char *str, int *width, va_list args)
{
	int	i;

	i = 0;
	if (ft_isdigit(str[i]))
		*width = ft_atoi(&str[i]);
	else if (str[i] == '*')
		*width = va_arg(args, int);
	while (ft_isdigit(str[i]) || str[i] == '*')
		i++;
	return (i);
}

int	ft_printprec(const char *str, int *prec, va_list args)
{
	int	i;

	i = 0;
	if (str[i] == '.')
	{
		i++;
		if (ft_isdigit(str[i]))
			*prec = ft_atoi(&str[i]);
		else if (str[i] == '*')
			*prec = va_arg(args, int);
		else
			*prec = -2;
		while (ft_isdigit(str[i]) || str[i] == '*')
			i++;
	}
	return (i);
}

int	ft_printtype(const char *str, t_param p, va_list args)
{
	int	count;

	count = 0;
	if (str[0] == 'c')
		count = count + ft_printc(p.flag, p.width, va_arg(args, int));
	else if (str[0] == 's')
		count += ft_prints(p.flag, p.width, p.prec, va_arg(args, char *));
	else if (str[0] == 'p')
		count += ft_printp(p.flag, p.width, p.prec, va_arg(args, void *));
	else if (str[0] == 'd' || str[0] == 'i')
		count += ft_printd(p.flag, p.width, p.prec, va_arg(args, int));
	else if (str[0] == 'u')
		count += ft_printu(p.flag, p.width, p.prec, va_arg(args, int));
	else if (str[0] == 'x')
		count += ft_printx(p.flag, p.width, p.prec, va_arg(args, int));
	else if (str[0] == 'X')
		count += ft_printx(p.flag + 32, p.width, p.prec, va_arg(args, int));
	else if (str[0] == '%')
		count = count + write (1, "%", 1);
	return (count);
}
