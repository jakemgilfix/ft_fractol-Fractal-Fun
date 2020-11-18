/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   another_iterator.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/13 11:24:53 by jgilfix           #+#    #+#             */
/*   Updated: 2020/02/13 12:57:01 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	cubic_julia(int x, int y, t_frac *frac)
{
	t_complex	z;
	t_complex	tmp;
	int			iter;

	z = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
					(float)(y - frac->orig.y) / frac->zoom};
	iter = 0;
	while ((++iter < frac->max_iter) && ((z.re * z.re + z.im * z.im) <= 4))
	{
		tmp = (t_complex){z.re * z.re * z.re - 3 * z.re * z.im * z.im
							+ frac->c.re,
						3 * z.re * z.re * z.im - z.im * z.im * z.im
							+ frac->c.im};
		z = tmp;
	}
	return (iter);
}
