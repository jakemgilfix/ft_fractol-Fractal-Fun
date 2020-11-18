/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 09:06:07 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:24:38 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** ft_printf.h   :   t_printf_spec, ftpf_putnum(), ftpf_putnum_base(),        **
**                   ftpf_putchar(), ftpf_putstr(), ftpf_putptr(),            **
**                   ftpf_putfloat(), ftpf_putpadding(), ftpf_buffer()        **
**    from stdarg.h   :   va_arg                                              **
** libft.h       :   ft_strchr(), ft_strindex(), ft_tolower()                 **
********************************************************************************
*/

#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_COLOR ******************************************************************
** ~ Handles conversion of (bonus) color specifier (e.g., %{red}), allowing   **
**   for beautifully colored output.                                          **
********************************************************************************
*/

static void	ftpf_color(t_printf_spec *spec)
{
	int			i;
	int			len;
	const char	*colors[] = {"{red}", "{green}", "{blue}", "{cyan}",
		"{magenta}", "{yellow}", "{nocolor}"};
	const char	*color_code[] = {C_RED, C_GREEN, C_BLUE, C_CYAN, C_MAGENTA,
		C_YELLOW, C_NOCOL};

	spec->printed = 5;
	len = 0;
	i = -1;
	while (++i < (int)(sizeof(colors) / sizeof(*colors)))
		if (!ft_strncmp(spec->format, colors[i], (len = ft_strlen(colors[i]))))
		{
			ftpf_buffer(spec, (char *)color_code[i], ft_strlen(color_code[i]));
			break ;
		}
	spec->format += len - 1;
}

/*
** INVALID_CONVERSION **********************************************************
** ~ Handles a non-matching `type` parameter given as part of a conversion    **
**   specification.                                                           **
********************************************************************************
*/

static void	invalid_conversion(t_printf_spec *spec)
{
	const char	c = (spec->flags & FL_ZERO) ? '0' : ' ';

	if (!*spec->format)
		return ;
	spec->padding = (spec->flags & FL_MINUS) ?
		0 : spec->width - 1;
	ftpf_putpadding(spec, c);
	ftpf_buffer(spec, spec->format, 1);
	spec->padding = (spec->flags & FL_MINUS) ?
		spec->width - 1 : 0;
	ftpf_putpadding(spec, c);
}

/*
** FTPF_FINISH_CONVERSION ******************************************************
** ~ Parses the conversion type and finishes the specified conversion         **
** ~ Conversion specification format:                                         **
**                   %[flags][width][.precision][size]type                    **
**   Supported conversions:                                                   **
**      d/i        :   integers                                               **
**      b/o/u/xX   :   binary/octal/unsigned int/hexadecimal                  **
**      c          :   ASCII character                                        **
**      s          :   string of ASCII characters                             **
**      p          :   pointer address                                        **
**      f/F        :   floating point number                                  **
********************************************************************************
*/

void		ftpf_finish_conversion(t_printf_spec *spec)
{
	spec->type = *spec->format;
	if (spec->type && ft_strchr("di", spec->type))
		ftpf_putnum(spec);
	else if (spec->type && ft_strchr("bouxX", spec->type))
	{
		spec->flags |= ft_isupper(spec->type) ? FL_UPPER : 0;
		ftpf_putnum_base(ft_strindex("$$b$$$$$o$u$$$$$x",
			ft_tolower(spec->type)), spec);
	}
	else if (spec->type == 'c')
		ftpf_putchar(spec, va_arg(spec->ap, unsigned int));
	else if (spec->type == 's')
		ftpf_putstr(spec);
	else if (spec->type == 'p')
		ftpf_putptr(spec);
	else if (ft_tolower(spec->type) == 'f')
		ftpf_putfloat(spec);
	else if (spec->type == '{')
		ftpf_color(spec);
	else
		invalid_conversion(spec);
}
