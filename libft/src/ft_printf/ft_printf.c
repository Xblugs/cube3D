/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/05 16:44:47 by cczerwin          #+#    #+#             */
/*   Updated: 2024/12/05 16:44:54 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include "libft.h"

//#include <limits.h>
// "%-0# +(width).(prec)(type)\0"
int	ft_printf(const char *str, ...);

int	ft_printf(const char *str, ...)
{
	const char	type_ok[10] = {'c', 's', 'p', 'd', 'i', 'u', 'x', 'X', '%', 0};
	int			i;
	int			count;
	t_param		par;
	va_list		args;

	va_start(args, str);
	i = 0;
	count = 0;
	while (str[i] != 0)
	{
		if (str[i] == '%')
		{
			i = i + ft_printinit(&str[i], &par, args);
			if (ft_isset(&str[i], type_ok))
				count += ft_printtype(&str[i], par, args);
			else
				count = count + write (1, "%", 1);
		}
		else
			count = count + write (1, &str[i], 1);
		i++;
	}
	va_end(args);
	return (count);
}
