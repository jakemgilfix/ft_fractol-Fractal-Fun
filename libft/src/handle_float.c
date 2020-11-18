/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_float.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/23 21:56:35 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:23:56 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** ft_printf.h   :   t_printf_spec, FL_PLUS, FL_BLANK, FL_PREC, FL_HASH,      **
**                   FL_MINUS, FL_ZERO, ftpf_buffer(), ftpf_putpadding()      **
**    from stdarg.h   :   va_arg                                              **
** libft.h       :   ft_int_max(), ft_power(), ft_ten_to_power()              **
********************************************************************************
*/

#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_FLOAT_SETUP_SPEC *******************************************************
** ~ Initializes `spec->printed`, `spec->prec`, and `spec->width`, returning  **
**   the number of digits in the whole part of `n` for use by                 **
**   ftpf_bufferize_float().                                                  **
********************************************************************************
*/

static int			ftpf_float_setup_spec(t_printf_spec *spec, long double n)
{
	int			digits_in_whole;
	__int128_t	whole_part;

	whole_part = (__int128_t)((n < 0.0) ? -n : n);
	spec->printed = 1 + ((spec->flags & (FL_PLUS | FL_BLANK)) || (n < 0.0));
	digits_in_whole = 1;
	while ((whole_part /= 10) && ++spec->printed)
		digits_in_whole++;
	spec->prec = (spec->flags & FL_PREC) ? spec->prec : 6;
	spec->printed += (spec->prec || (spec->flags & FL_HASH)) + spec->prec;
	spec->width = ft_int_max(spec->width, spec->printed);
	return (digits_in_whole);
}

/*
** FTPF_FLOAT_GETDEC ***********************************************************
** ~ Returns the first `spec->prec` digits after the decimal in `n` formatted **
**   as a __int128_t.                                                         **
********************************************************************************
*/

static __int128_t	ftpf_float_getdec(t_printf_spec *spec, long double n)
{
	__int128_t	long_dec;

	n *= ft_power(10, spec->prec + 1);
	long_dec = (__int128_t)n;
	long_dec += ((long_dec % 10) > 4) ? 10 : 0;
	return (long_dec / 10);
}

/*
** FTPF_FLOAT_PUTNDIG **********************************************************
** ~ Puts `digits` number of digits of number `n` into the print buffer.      **
********************************************************************************
*/

static void			ftpf_float_putndig(t_printf_spec *spec,
	__int128_t n, int digits)
{
	char		buffer[48];
	const int	digits_cpy = digits;

	while (digits--)
	{
		buffer[digits] = n % 10 + '0';
		n /= 10;
	}
	ftpf_buffer(spec, buffer, digits_cpy);
}

/*
** FTPF_BUFFERIZE_FLOAT ********************************************************
** ~ Puts the floating point number `n` into the print buffer, formatted      **
**   according to the conversion specification provided.                      **
********************************************************************************
*/

static void			ftpf_bufferize_float(t_printf_spec *spec, long double n,
	int digits_in_whole)
{
	char		c;
	__int128_t	whole_part;
	__int128_t	dec_part;

	spec->padding = (spec->flags & (FL_MINUS | FL_ZERO)) ?
		0 : spec->width - spec->printed;
	ftpf_putpadding(spec, (spec->flags & FL_ZERO) ? '0' : ' ');
	if ((n < 0.0) || (spec->flags & (FL_PLUS | FL_BLANK)))
	{
		c = (spec->flags & FL_PLUS) ? '+' : ' ';
		ftpf_buffer(spec, (n < 0.0) ? "-" : &c, 1);
	}
	spec->padding = (spec->flags & FL_ZERO) ? spec->width - spec->printed : 0;
	ftpf_putpadding(spec, '0');
	whole_part = (__int128_t)((n < 0.0) ? -n : n);
	dec_part = ftpf_float_getdec(spec, ((n < 0.0) ? -n : n) - whole_part);
	(dec_part == ft_ten_to_power(spec->prec)) ? whole_part++ : 0;
	ftpf_float_putndig(spec, whole_part, digits_in_whole);
	if (spec->prec || (spec->flags & FL_HASH))
		ftpf_buffer(spec, ".", 1);
	ftpf_float_putndig(spec, dec_part, spec->prec);
	spec->padding = (spec->flags & FL_MINUS) ? spec->width - spec->printed : 0;
	ftpf_putpadding(spec, ' ');
}

/*
** FTPF_PUTFLOAT ***************************************************************
** ~ Handles conversion of 'f' `type`.                                        **
** ~ Called by ftpf_finish_conversion() (in parser2.c).                       **
********************************************************************************
*/

void				ftpf_putfloat(t_printf_spec *spec)
{
	long double	n;
	long double	dec_part;
	__int128_t	whole_part;

	n = (spec->size == sz_L) ?
		va_arg(spec->ap, long double) : va_arg(spec->ap, double);
	whole_part = (__int128_t)((n < 0.0) ? -n : n);
	dec_part = ((n < 0.0) ? -n : n) - whole_part;
	ftpf_bufferize_float(spec, n, ftpf_float_setup_spec(spec, n));
}
