/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:51:15 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/30 15:51:19 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

# include "libft.h"

# ifndef HEX_L
#  define HEX_L "0123456789abcdef"
# endif

# ifndef HEX_U
#  define HEX_U "0123456789ABCDEF"
# endif

typedef struct s_param
{
	int			flag;
	int			width;
	int			prec;
}	t_param;

///////////		Print related		///////////

int				ft_printf(const char *str, ...);

///////////		ft_parsing		///////////

int				ft_printinit(const char *str, t_param *p, va_list args);
int				ft_printflag(const char *str, int *flag);
int				ft_printwidth(const char *str, int *width, va_list args);
int				ft_printprec(const char *str, int *prec, va_list args);
int				ft_printtype(const char *str, t_param p, va_list args);

///////////		ft_padding			///////////

int				ft_padding(int flag, int n);
int				ft_printsign(int flag, int data);
int				ft_printpref(int flag, int data);

///////////			ft_print[type]				///////////

int				ft_printc(int flag, int width, int data);
int				ft_prints(int flag, int width, int prec, char *sdata);

int				ft_printd(int flag, int width, int prec, int data);

int				ft_printu(int flag, int width, int prec, unsigned int data);

int				ft_printx(int flag, int width, int prec, unsigned int data);

int				ft_printp(int flag, int width, int prec, void *data);

///////////		ft_util		///////////

extern int		ft_isdigit(int c);
extern int		ft_isset(char const *s, char const *set);
extern int		ft_int_strlen(const char *s);

///////////		ft_util_pow		///////////

int				ft_rec_expo(int nb);
int				ft_rec_expo_u(unsigned int nb);
int				ft_rec_expo_base(unsigned long nb, int base);
unsigned long	ft_iter_pow(unsigned long nb, unsigned long power);

///////////		Misc		///////////

int				ft_atoi(const char *nptr);

#endif
