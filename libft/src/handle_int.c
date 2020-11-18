/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_int.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 09:56:16 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:24:08 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** ft_printf.h   :   t_printf_spec, t_sz_spec, FL_PREC, FL_PLUS, FL_ZERO,     **
**                   FL_BLANK, FL_HASH, FL_POINTER, ftpf_putpadding(),        **
**                   ftpf_buffer()                                            **
**     from stdarg.h     :   va_arg                                           **
**     from inttypes.h   :   intmax_t, uintmax_t                              **
** libft.h       :   ft_int_max()                                             **
********************************************************************************
*/

#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_ITOA_FILL **************************************************************
** ~ Utility function used by both ftpf_itoa() and ftpf_itoa_base() that      **
**   fills up the `res` buffer appropriately.                                 **
********************************************************************************
*/

static void	ftpf_itoa_fill(uintmax_t n, int base, char buff[25],
	t_printf_spec *spec)
{
	int		i;
	char	offset;

	i = spec->printed;
	offset = (spec->flags & FL_UPPER) ? 'A' - 10 : 'a' - 10;
	while (i--)
	{
		buff[i] = n % base + ((n % base < 10) ? '0' : offset);
		n /= base;
	}
}

/*
** FTPF_ITOA *******************************************************************
** ~ Puts `n` into the print buffer, formatted according to the conversion    **
**   specification given.                                                     **
** ~ How it works:                                                            **
**      spec->printed := number of digits in `n`                              **
**      If no precision was specified and the '0' flag was set:               **
**         spec->prec := spec->width (minus 1 if there needs to be a sign)    **
**      spec->printed := max(spec->printed, spec->prec)                       **
**      If n is negative, or ' '/'+' flags are set:                           **
**         Need an extra sign character -> spec->printed++                    **
**      spec->width := ACTUAL width = max(spec->printed, spec->width)         **
**      If '-' flag is NOT set, left pad with `spec->width` - `spec->printed` **
**       many spaces                                                          **
**      Fill `n` into the buffer                                              **
**      The buffer has enough space for a sign or a blank, if necessary, so   **
**       put it in there                                                      **
**      Put the `buffer` into the print buffer                                **
**      Fill in the right padding                                             **
********************************************************************************
*/

static void	ftpf_itoa(intmax_t n, t_printf_spec *spec)
{
	uintmax_t		abs_n;
	char			buffer[25];
	const intmax_t	cpy_n = n;

	abs_n = (uintmax_t)(n < 0 ? -n : n);
	spec->printed = 0;
	while (abs_n && ++spec->printed)
		abs_n /= 10;
	if (!(spec->flags & FL_PREC) && (spec->flags & FL_ZERO))
		spec->prec =
			spec->width - ((n < 0) || (spec->flags & (FL_PLUS | FL_BLANK)));
	spec->printed = ft_int_max(spec->printed, spec->prec);
	if ((n < 0) || (spec->flags & (FL_BLANK | FL_PLUS)))
		spec->printed++;
	spec->width = ft_int_max(spec->printed, spec->width);
	spec->padding = (spec->flags & FL_MINUS) ? 0 : spec->width - spec->printed;
	ftpf_putpadding(spec, ' ');
	ftpf_itoa_fill((uintmax_t)(n < 0 ? -n : n), 10, buffer, spec);
	if ((cpy_n >= 0) && (spec->flags & (FL_BLANK | FL_PLUS)))
		buffer[0] = (spec->flags & FL_PLUS) ? '+' : ' ';
	else if ((long long)cpy_n < 0)
		buffer[0] = '-';
	ftpf_buffer(spec, buffer, spec->printed);
	spec->padding = (spec->flags & FL_MINUS) ? spec->width - spec->printed : 0;
	ftpf_putpadding(spec, ' ');
}

/*
** FTPF_ITOA_BASE **************************************************************
** ~ Puts `n` (in base `base`) into the print buffer, formatted according to  **
**   the conversion specification given.                                      **
********************************************************************************
*/

void		ftpf_itoa_base(uintmax_t n, int base, t_printf_spec *spec)
{
	const uintmax_t	cpy_n = n;
	char			buffer[50];

	spec->printed = (!n && (spec->flags & FL_HASH) && (base == 8)) ? 1 : 0;
	spec->printed += (!n && (base == 16) && (spec->flags & FL_POINTER));
	while (n && ++spec->printed)
		n /= base;
	n = cpy_n;
	if (!(spec->flags & FL_PREC) && (spec->flags & FL_ZERO))
		spec->prec = spec->width;
	else if ((spec->flags & FL_PREC) && (spec->flags & FL_HASH) && (base == 16))
		spec->printed = ft_int_max(spec->prec, spec->printed);
	if ((n && (spec->flags & FL_HASH)) || (spec->flags & FL_POINTER))
		spec->printed += 2 * (base == 16) + (base == 8);
	spec->printed = ft_int_max(spec->printed, spec->prec);
	spec->width = ft_int_max(spec->printed, spec->width);
	spec->padding = (spec->flags & FL_MINUS) ? 0 : spec->width - spec->printed;
	ftpf_putpadding(spec, ' ');
	ftpf_itoa_fill(n, base, buffer, spec);
	if (((cpy_n && (spec->flags & FL_HASH)) || (spec->flags & FL_POINTER)) &&
		(buffer[0] = '0'))
		(base == 16) ? buffer[1] = spec->type : 0;
	ftpf_buffer(spec, buffer, spec->printed);
	spec->padding = (spec->flags & FL_MINUS) ? spec->width - spec->printed : 0;
	ftpf_putpadding(spec, ' ');
}

/*
** FTPF_PUTNUM *****************************************************************
** ~ Handles conversion of `type`s 'd'/'i'.                                   **
** ~ Called by ftpf_finish_conversion() (in parser2.c).                       **
********************************************************************************
*/

void		ftpf_putnum(t_printf_spec *spec)
{
	intmax_t	n;

	if (spec->size == sz_hh)
		n = (intmax_t)((char)va_arg(spec->ap, int));
	else if (spec->size == sz_h)
		n = (intmax_t)((short)va_arg(spec->ap, int));
	else if (spec->size == sz_l || spec->size == sz_L)
		n = (intmax_t)va_arg(spec->ap, long);
	else if (spec->size == sz_ll)
		n = (intmax_t)va_arg(spec->ap, long long);
	else if (spec->size == sz_j)
		n = va_arg(spec->ap, intmax_t);
	else if (spec->size == sz_z)
		n = (intmax_t)va_arg(spec->ap, ssize_t);
	else
		n = (intmax_t)va_arg(spec->ap, int);
	ftpf_itoa(n, spec);
}

/*
** FTPF_PUTNUM_BASE ************************************************************
** ~ Handles conversion of `type`s 'b'/'o'/'u'/'x'/'X', as well as 'p'.       **
** ~ Called by ftpf_finish_conversion() (in parser2.c).                       **
********************************************************************************
*/

void		ftpf_putnum_base(int base, t_printf_spec *spec)
{
	uintmax_t	n;

	if (spec->size == sz_hh)
		n = (uintmax_t)((unsigned char)va_arg(spec->ap, int));
	else if (spec->size == sz_h)
		n = (uintmax_t)((unsigned short)va_arg(spec->ap, int));
	else if (spec->size == sz_l)
		n = (intmax_t)va_arg(spec->ap, unsigned long);
	else if (spec->size == sz_ll)
		n = (intmax_t)va_arg(spec->ap, unsigned long long);
	else if (spec->size == sz_j)
		n = va_arg(spec->ap, uintmax_t);
	else if (spec->size == sz_z)
		n = (uintmax_t)va_arg(spec->ap, size_t);
	else
		n = (uintmax_t)va_arg(spec->ap, unsigned int);
	ftpf_itoa_base(n, base, spec);
}
