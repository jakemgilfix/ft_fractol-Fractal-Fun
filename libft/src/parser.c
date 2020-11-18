/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 17:29:39 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:24:30 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** unistd.h      :   write()                                                  **
** ft_printf.h   :   t_printf_spec, FL_MINUS, FL_PLUS, FL_ZERO, FL_BLANK,     **
**                   t_sz_spec, ftpf_buffer()                                 **
**    from stdarg.h   :   va_list, va_start, va_arg                           **
** libft.h       :   ft_strindex(), ft_isdigit(), ft_int_max(), ft_atoi()     **
********************************************************************************
*/

#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

/*
** PARSE_FLAGS *****************************************************************
** ~ Parses (optional) flags in conversion specifier : {-, +, 0, <BLANK>, #}  **
** ~ Conversion specification format:                                         **
**                   %[flags][width][.precision][size]type                    **
** ~ Notes:                                                                   **
**      a) If both '0' and '-' appear, '0' is IGNORED.                        **
**      b) If both ' ' and '+' appear, the ' ' is IGNORED.                    **
********************************************************************************
*/

static void	parse_flags(t_printf_spec *spec)
{
	int	i;

	while ((i = ft_strindex("-+0 #", *(spec->format))) != -1)
	{
		spec->format++;
		spec->flags |= (1 << i);
	}
	if (spec->flags & FL_MINUS)
		spec->flags &= ~FL_ZERO;
	if (spec->flags & FL_PLUS)
		spec->flags &= ~FL_BLANK;
}

/*
** PARSE_WIDTH_AND_PREC ********************************************************
** ~ Parses (optional) width and precision specified in conversion specifier  **
** ~ Conversion specification format:                                         **
**                   %[flags][width][.precision][size]type                    **
** ~ Notes:                                                                   **
**      a) `width` controls the minimum number of characters that are output. **
**      b) `precision` (depending on the conversion type) controls the number **
**         of string characters, the number of decimal places, or the number  **
**         of significant digits to be output.                                **
********************************************************************************
*/

static void	parse_width_and_prec(t_printf_spec *spec)
{
	if (ft_isdigit(*spec->format) && (*spec->format != '0'))
	{
		spec->width = ft_int_max(1, ft_atoi(spec->format));
		while (ft_isdigit(*spec->format))
			spec->format++;
	}
	else if (*spec->format == '*' && spec->format++)
		spec->width = (int)va_arg(spec->ap, int);
	if (*spec->format == '.' && spec->format++)
	{
		spec->flags |= FL_PREC;
		spec->prec = (*spec->format == '*' && spec->format++) ?
			ft_int_max(-1, (int)va_arg(spec->ap, int)) :
			ft_int_max(-1, ft_atoi(spec->format));
		if (spec->prec < 0)
		{
			spec->flags &= ~FL_PREC;
			spec->prec = 0;
		}
		while (ft_isdigit(*spec->format))
			spec->format++;
	}
}

/*
** PARSE_SIZE ******************************************************************
** ~ Parses (optional) size specifiers : {l, ll, h, hh, j, z}                 **
** ~ Required by ft_printf:                                                   **
**      hh   :   char/unsigned char, with type specs d/i/o/u/x/X              **
**      h    :   short int/short unsigned int, with type specs d/i/o/u/x/X    **
**      l    :   long int/long unsigned int, with type specs d/i/o/u/x/X, OR  **
**               long double, with type specifier f                           **
**      L    :   long double, with type specifier f                           **
**      ll   :   long long int/unsigned long long int, with d/i/o/u/x/X       **
** ~ BONUS:                                                                   **
**      j    :   intmax_t, with type specifiers d/i/o/u/x/X                   **
**      z    :   size_t, with type specifiers d/i/o/u/x/X                     **
********************************************************************************
*/

static void	parse_size(t_printf_spec *spec)
{
	while (1)
	{
		if (*spec->format == 'h')
			spec->size = (*(spec->format + 1) == 'h' && ++spec->format) ?
				sz_hh : sz_h;
		else if (*spec->format == 'l')
			spec->size = (*(spec->format + 1) == 'l' && ++spec->format) ?
				sz_ll : sz_l;
		else if (*spec->format == 'L')
			spec->size = sz_L;
		else if (*spec->format == 'j' || *spec->format == 'z')
			spec->size = (*spec->format == 'j') ? sz_j : sz_z;
		else
			break ;
		spec->format++;
	}
}

/*
** PARSE_CS() ******************************************************************
** ~ Parses conversion specifier given as part of format string. Conversion   **
**   specifiers follow this format:                                           **
**                    %[flags][width][.precision][size]type                   **
** ~ By default:                                                              **
**      a) NONE of the flags are set.                                         **
**      b) Minimum field width is 0 (small widths will NOT cause truncation)  **
**      c) Size is `sz_default`.                                              **
** ~ Default precision varies with conversion type. The size field modifies   **
**   the type (e.g., hhd -> unsigned char; hd -> short int; etc.).            **
********************************************************************************
*/

static void	parse_cs(t_printf_spec *spec)
{
	spec->flags = 0;
	spec->width = 0;
	spec->prec = 1;
	spec->size = sz_default;
	parse_flags(spec);
	parse_width_and_prec(spec);
	parse_size(spec);
	parse_flags(spec);
	if (spec->flags & FL_PLUS)
		spec->flags &= ~FL_BLANK;
	if (*spec->format == 'X')
		spec->size = sz_l;
	ftpf_finish_conversion(spec);
}

/*
** PARSE_FORMAT() **************************************************************
** ~ Parses the format string given to `ft_*printf()` and stored in the       **
**   structure pointed to by `spec`.                                          **
********************************************************************************
*/

int			parse_format(t_printf_spec *spec)
{
	while (*(spec->format))
	{
		if (*(spec->format) == '%')
		{
			if (!(*(++(spec->format))))
				break ;
			parse_cs(spec);
		}
		else
			ftpf_buffer(spec, spec->format, 1);
		spec->format += (*spec->format != '\0');
	}
	write(spec->fd, spec->buffer, spec->buffer_idx);
	return (spec->char_count);
}
