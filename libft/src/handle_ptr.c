/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_ptr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 11:13:37 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:24:17 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** ft_printf.h   :   t_printf_spec, FL_ZERO, FL_HASH, FL_POINTER,             **
**                   ftpf_itoa_base()                                         **
**     from stdarg.h     :   va_arg                                           **
**     from inttypes.h   :   uintmax_t                                        **
** libft.h       :   ft_int_max()                                             **
********************************************************************************
*/

#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_PUTPTR *****************************************************************
** ~ Handles conversion of 'p' `type` by calling ftpf_itoa_base() (in         **
**   handle_int.c).                                                           **
** ~ Called by ftpf_finish_conversion() (in parser2.c).                       **
********************************************************************************
*/

void	ftpf_putptr(t_printf_spec *spec)
{
	void	*ptr;

	ptr = va_arg(spec->ap, void *);
	spec->width -= (spec->flags & FL_ZERO) ? 2 : 0;
	spec->padding = ft_int_max(0, spec->width - spec->printed - 3);
	spec->flags |= (FL_HASH | FL_POINTER);
	spec->type = 'x';
	ftpf_itoa_base((uintmax_t)ptr, 16, spec);
}
