/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strindex.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/16 08:59:22 by jgilfix           #+#    #+#             */
/*   Updated: 2020/01/23 23:07:51 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** FT_STRINDEX *****************************************************************
** ~ Returns the index of the first occurence of `c` in `str`, if found.      **
**   Otherwise, returns -1.                                                   **
********************************************************************************
*/

int		ft_strindex(const char *str, char c)
{
	char	*ptr;

	return ((c && (ptr = ft_strchr(str, c))) ? (int)(ptr - str) : -1);
}
