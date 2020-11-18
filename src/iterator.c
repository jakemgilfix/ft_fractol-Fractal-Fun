/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   iterator.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:31:08 by jgilfix           #+#    #+#             */
/*   Updated: 2020/02/13 11:43:12 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int	mandelbrot(int x, int y, t_frac *frac)
{
	t_complex	c;
	t_complex	z;
	t_complex	tmp;
	int			iter;

	c = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
					(float)(y - frac->orig.y) / frac->zoom};
	z = (t_complex){0, 0};
	iter = 0;
	while ((++iter < frac->max_iter) && ((z.re * z.re + z.im * z.im) <= 4))
	{
		tmp = (t_complex){z.re * z.re - z.im * z.im + c.re,
							2 * z.re * z.im + c.im};
		z = tmp;
	}
	return (iter);
}

/*
** JULIA FRACTAL ***************************************************************
** ~ Same as Mandelbrot, but z comes from the pixel location and c comes from **
**     the mouse location.                                                    **
********************************************************************************
*/

int	julia(int x, int y, t_frac *frac)
{
	t_complex	z;
	t_complex	tmp;
	int			iter;

	z = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
					(float)(y - frac->orig.y) / frac->zoom};
	iter = 0;
	while ((++iter < frac->max_iter) && ((z.re * z.re + z.im * z.im) <= 4))
	{
		tmp = (t_complex){z.re * z.re - z.im * z.im + frac->c.re,
							2 * z.re * z.im + frac->c.im};
		z = tmp;
	}
	return (iter);
}

int	tricorn(int x, int y, t_frac *frac)
{
	t_complex	c;
	t_complex	z;
	t_complex	tmp;
	int			iter;

	c = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
									(float)(y - frac->orig.y) / frac->zoom};
	z = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
					(float)(y - frac->orig.y) / frac->zoom};
	iter = 0;
	while ((++iter < frac->max_iter) && ((z.re * z.re + z.im * z.im) <= 4))
	{
		tmp = (t_complex){z.re * z.re - z.im * z.im + c.re,
							-2 * z.re * z.im + c.im};
		z = tmp;
	}
	return (iter);
}

int	burning_ship(int x, int y, t_frac *frac)
{
	t_complex	c;
	t_complex	z;
	t_complex	tmp;
	int			iter;

	c = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
					(float)(y - frac->orig.y) / frac->zoom};
	z = c;
	iter = 0;
	while ((++iter < frac->max_iter) && ((z.re * z.re + z.im * z.im) <= 4))
	{
		tmp = (t_complex){(float)fabs(z.re * z.re - z.im * z.im + c.re),
							(float)fabs(2 * z.re * z.im + c.im)};
		z = tmp;
	}
	return (iter);
}

int	mod_julia(int x, int y, t_frac *frac)
{
	t_complex	z;
	t_complex	tmp;
	int			iter;

	z = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
					(float)(y - frac->orig.y) / frac->zoom};
	iter = 0;
	while ((++iter < frac->max_iter) && ((z.re * z.re + z.im * z.im) <= 4))
	{
		tmp = (t_complex){z.re * z.re - z.im * z.im + frac->c.re,
							2 * z.re * z.im + frac->c.im};
		z = tmp;
		if (1.0f / (z.re * z.re + z.im * z.im) > 4)
			break ;
	}
	return (iter);
}
