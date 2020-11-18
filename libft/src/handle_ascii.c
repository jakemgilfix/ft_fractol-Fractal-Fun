/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ascii.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 10:59:09 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:23:43 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** ft_printf.h   :   t_printf_spec, FL_MINUS, FL_PREC, ft_putpadding(),       **
**                   ft_buffer()                                              **
**    from stdarg.h   :   va_arg                                              **
** libft.h       :   ft_int_max(), ft_int_min(), ft_strlen()                  **
********************************************************************************
*/

#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_PUTCHAR ****************************************************************
** ~ Handles conversion of 'c' `type`.                                        **
** ~ Called by ftpf_finish_conversion() (in parser2.c).                       **
********************************************************************************
*/

void	ftpf_putchar(t_printf_spec *spec, unsigned int c)
{
	spec->printed = 1;
	spec->padding = (spec->flags & FL_MINUS) ?
		0 : ft_int_max(0, spec->width - spec->printed);
	ftpf_putpadding(spec, ' ');
	ftpf_buffer(spec, (char *)&c, 1);
	spec->padding = (spec->flags & FL_MINUS) ?
		ft_int_max(0, spec->width - spec->printed) : 0;
	ftpf_putpadding(spec, ' ');
}

/*
** FTPF_PUTSTR *****************************************************************
** ~ Handles conversion of 's' `type`.                                        **
** ~ Called by ftpf_finish_conversion() (in parser2.c).                       **
********************************************************************************
*/

void	ftpf_putstr(t_printf_spec *spec)
{
	unsigned int	*str;
	int				len;

	str = va_arg(spec->ap, unsigned int *);
	len = str ? (int)ft_strlen((char *)str) : 6;
	len = (spec->flags & FL_PREC) ? ft_int_min(spec->prec, len) : len;
	spec->padding = (spec->flags & FL_MINUS) ?
		0 : ft_int_max(0, spec->width - len);
	ftpf_putpadding(spec, ' ');
	ftpf_buffer(spec, str ? (char *)str : "(null)", len);
	spec->padding = (spec->flags & FL_MINUS) ?
		ft_int_max(0, spec->width - len) : 0;
	ftpf_putpadding(spec, ' ');
}
