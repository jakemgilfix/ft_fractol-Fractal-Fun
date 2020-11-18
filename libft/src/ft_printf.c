/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/15 16:58:12 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:23:30 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** unistd.h      :   STDOUT_FILENO                                            **
** ft_printf.h   :   t_printf_spec, parse_format()                            **
**    from stdarg.h   :   va_list, va_start, va_arg, va_end                   **
** libft.h       :   ft_memset()                                              **
********************************************************************************
*/

#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_SPEC_INIT **************************************************************
** ~ Initializes the structure containing all the pertinent information about **
**   the specified conversion(s).                                             **
********************************************************************************
*/

static void	ftpf_spec_init(t_printf_spec *spec, int fd, const char *format)
{
	if (spec)
	{
		ft_memset(spec, 0, sizeof(*spec));
		spec->fd = fd;
		spec->format = (char *)format;
	}
}

/*
** FT_PRINTF *******************************************************************
** ~ The main show. Calls `parse_format()` (located in parser.c), which does  **
**     all the actual work.                                                   **
********************************************************************************
*/

int			ft_printf(const char *format, ...)
{
	int				result;
	t_printf_spec	spec;

	ftpf_spec_init(&spec, STDOUT_FILENO, format);
	va_start(spec.ap, format);
	result = parse_format(&spec);
	va_end(spec.ap);
	return (result);
}

/*
** FT_DPRINTF ******************************************************************
** ~ Same as `ft_printf()`, but prints the output to file descriptor `fd`.    **
********************************************************************************
*/

int			ft_dprintf(int fd, const char *format, ...)
{
	int				result;
	t_printf_spec	spec;

	ftpf_spec_init(&spec, fd, format);
	va_start(spec.ap, format);
	result = parse_format(&spec);
	va_end(spec.ap);
	return (result);
}
