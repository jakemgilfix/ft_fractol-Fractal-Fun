/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   buffer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 09:17:14 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/26 17:23:15 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INCLUDES ********************************************************************
** unistd.h      :   write()                                                  **
** ft_printf.h   :   t_printf_spec, FTPF_BUFF_SIZE                            **
**     from inttypes.h   :   intmax_t                                         **
** libft.h       :   ft_memcpy()                                              **
********************************************************************************
*/

#include <unistd.h>
#include "ft_printf.h"
#include "libft.h"

/*
** FTPF_BUFFER *****************************************************************
** ~ Adds string `to_add` (`size` bytes long) to the print buffer, writing    **
**   the contents of the buffer to `spec->fd` if the buffer is full.          **
********************************************************************************
*/

void	ftpf_buffer(t_printf_spec *spec, char *to_add, int size)
{
	intmax_t	i;
	intmax_t	bytes_left;

	i = 0;
	while ((spec->buffer_idx + size) > FTPF_BUFF_SIZE)
	{
		bytes_left = FTPF_BUFF_SIZE - spec->buffer_idx;
		ft_memcpy(spec->buffer + spec->buffer_idx, to_add + i, bytes_left);
		size -= bytes_left;
		i += bytes_left;
		spec->buffer_idx += bytes_left;
		spec->char_count += bytes_left;
		write(spec->fd, spec->buffer, spec->buffer_idx);
		spec->buffer_idx = 0;
	}
	if (size)
	{
		ft_memcpy(spec->buffer + spec->buffer_idx, to_add + i, size);
		spec->buffer_idx += size;
		spec->char_count += size;
	}
}

/*
** FTPF_PUTPADDING *************************************************************
** ~ Puts `spec->padding` many `c`s into the print buffer.                    **
********************************************************************************
*/

void	ftpf_putpadding(t_printf_spec *spec, char c)
{
	while (spec->padding-- > 0)
		ftpf_buffer(spec, &c, 1);
}
