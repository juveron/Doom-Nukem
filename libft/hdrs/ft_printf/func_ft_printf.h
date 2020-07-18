/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_ft_printf.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/11 13:21:27 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:08:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNC_FT_PRINTF_H
# define FUNC_FT_PRINTF_H

# include <stdarg.h>
# ifdef __unix__
#  include <inttypes.h>
# endif
# include "libft.h"
# include "bigint.h"

# define PRINTF_BUFFER_SIZE 4096

# define PREFIX_FLAG 0
# define ZERO_FLAG 1
# define LEFT_FLAG 2
# define SPACE_FLAG 3
# define SIGN_FLAG 4

# define LOG10_2 0.30102999566398119521373889472449

typedef void	(*t_func)();

typedef struct	s_struct64
{
	t_u64	mant : 52;
	t_u32	exp : 11;
	t_u8	sign : 1;
}				t_struct64;

typedef union	u_float64
{
	double		dvalue;
	t_u64		lvalue;
	t_struct64	struct64;
}				t_float64;

typedef struct	s_struct128
{
	t_u64	mant;
	t_u32	exp : 15;
	t_u8	sign : 1;
}				t_struct128;

typedef union	u_float128
{
	long double		ldvalue;
	t_struct128		struct128;
}				t_float128;

typedef struct	s_string_float
{
	char	str[22000];
	int		size_str;
	int		nb_bit;
	int		final_size_str;
	int		size_exponent;
	int		out_exponent;
	int		size_fraction;
	int		size_added_frac;
	int		sign;
}				t_string_float;

typedef struct	s_format_float
{
	t_s32			exp;
	t_u64			mant;
	t_u64			mant2;
	t_u64			output_digit;
	t_u32			mant_index;
	t_s32			digit_exponent;
	t_string_float	*string;
	char			*current_digit;
	char			*last_digit;
	t_bigint		scale;
	t_bigint		scaled_value;
	int				cutoff_exponent;
	int				tmp2;
	bool			zero;
}				t_format_float;

typedef struct	s_float_func
{
	t_float64	float64;
	t_float128	float128;
	t_u64		mant;
	t_u32		exp;
	int			sign;
	int			nb_bits;
}				t_float_func;

typedef enum	e_size
{
	NONE,
	HH,
	H,
	LL,
	L,
	LONG,
	J,
	Z
}				t_size;

typedef struct	s_printf
{
	va_list	arg;
	int		ret;
	int		fd;
	char	buff[PRINTF_BUFFER_SIZE];
	size_t	pos_buff;
	char	*out;
	size_t	size_out;
	char	*format;
	char	*next;
	char	flag;
	bool	has_width;
	int		width;
	bool	has_precision;
	int		precision;
	t_size	size;
	t_func	*conv_func;
	bool	as;
	bool	sn;
	size_t	size_max_sn;
	bool	sn_no_space;
}				t_printf;

/*
**	ft_vdprintf.c
*/

void			ft_vdprintf(t_printf *pf);
t_func			*static_fun(void);

/*
**	length_unbr_base.c
*/

size_t			length_unbr_base(uintmax_t nb, size_t length_base);

/*
**	ft_flush.c
*/

void			ft_flush(t_printf *pf);

/*
**	put_buffer.c
*/

void			put_buffer(t_printf *pf, char c);
void			put_buffer_2(t_printf *pf, char c);

/*
**	padded.c
*/

void			padded(t_printf *pf, int length, char pad_char);

/*
**	putunbr_base.c
*/

void			putunbr_base(t_printf *pf, uintmax_t nb, char *base,
					uintmax_t size_base);

/*
**	integer.c
*/

void			func_integer(t_printf *pf);

/*
**	string.c
*/

void			func_string(t_printf *pf);

/*
**	percent.c
*/

void			func_percent(t_printf *pf);

/*
**	pointer.c
*/

void			func_pointer(t_printf *pf);

/*
**	unsigned.c
*/

void			func_unsigned(t_printf *pf);

/*
**	putwchar.c
*/

void			putwchar(t_printf *pf, wchar_t c);

/*
**	putwstr.c
*/

void			putnwstr(t_printf *pf, wchar_t *str, size_t n);

/*
**	wstrlen.c
*/

size_t			wstrlen(wchar_t *str);

/*
**	wcharlen.c
*/

size_t			wcharlen(wchar_t c);

/*
**	wchar.c
*/

void			func_wchar(t_printf *pf);

/*
**	char.c
*/

void			func_char(t_printf *pf);

/*
**	putnbr_buffer.c
*/

void			putnbr_buffer(t_printf *pf, int n);

/*
**	putstr_buffer.c
*/

void			putstr_buffer(t_printf *pf, char *str, size_t n);
void			putstr_buffer_2(t_printf *pf, char *str, size_t n);

/*
**	hex.c
*/

void			func_hex(t_printf *pf);

/*
**	wstr.c
*/

void			func_wstr(t_printf *pf);

/*
**	hexx.c
*/

void			func_hexx(t_printf *pf);

/*
**	octal.c
*/

void			func_octal(t_printf *pf);

/*
**	binary.c
*/

void			func_binary(t_printf *pf);

/*
**	ft_vdprintf_support.c
*/

void			check_flag(t_printf *pf);
void			get_flag(t_printf *pf);
int				get_width(t_printf *pf);
int				get_precision(t_printf *pf);
void			get_size(t_printf *pf);

/*
**	revert_bit.c
*/

t_u64			reverse_bits(t_u64 value);

/*
**	float.c
*/

void			func_float(t_printf *pf);

/*
**	ft_star.c
*/

void			ft_width_star(t_printf *pf);
int				ft_precision_star(t_printf *pf);
void			round_float(t_format_float *f);
void			func_double128(long double dvalue, int precision,
	t_string_float *string);
void			print_bigint(t_bigint *bigint);
void			func_double64(double dvalue,
	int precision, t_string_float *string);

/*
**	float_dunc.c
*/

void			normalize_scale(t_format_float *f);
void			compute_float(t_format_float *f);
void			add_point(t_format_float *f, int precision);
void			add_digit_exp(t_format_float *f);

/*
**	ft_color.c
*/

size_t			ft_color(t_printf *pf, char *str, size_t pos);

/*
**	raw.c
*/

void			func_raw(t_printf *pf);

#endif
