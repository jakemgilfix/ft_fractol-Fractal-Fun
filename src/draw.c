/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 11:06:57 by jgilfix           #+#    #+#             */
/*   Updated: 2020/02/13 13:03:22 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <pthread.h>

void		reset_defaults(t_frac *frac)
{
	frac->orig = (t_point){WIN_W / 2, WIN_H / 2};
	frac->zoom = WIN_H / 3;
	frac->max_iter = 50;
}

int			colorize(int n, t_frac *frac)
{
	const float	percent = (float)n / (float)(frac->max_iter);
	const int	wes_anderson[5] = {0x00edcb64, 0x00deb18b, 0x002e604a,
									0x00d1362f, 0x0027223C};

	if (percent < .14)
		return ((int)(percent / .14f * wes_anderson[0]));
	if (percent < .42)
		return ((int)(percent / .42f * wes_anderson[1]));
	if (percent < .69)
		return ((int)(percent / .69f * wes_anderson[2]));
	if (percent < .84)
		return ((int)(percent / .84f * wes_anderson[3]));
	return (percent * wes_anderson[4]);
}

static void	*draw_thread(void *thread_params)
{
	t_thr_params	*params;
	int				x;
	int				y;
	int				iter;

	params = (t_thr_params *)thread_params;
	y = params->thread;
	while (y < WIN_H)
	{
		x = -1;
		while (++x < WIN_W)
		{
			iter = params->frac->iter(x, y, params->frac);
			params->frac->data[x + y * WIN_W] = colorize(iter, params->frac);
		}
		y += 4;
	}
	return (NULL);
}

void		put_fractol_to_image(t_frac *frac)
{
	pthread_t		threads[4];
	t_thr_params	params[4];
	int				i;

	i = -1;
	while (++i < 4)
	{
		params[i].frac = frac;
		params[i].thread = i;
		pthread_create(&threads[i], NULL, draw_thread, (void *)(&(params[i])));
	}
	i = -1;
	while (++i < 4)
		pthread_join(threads[i], 0);
}

void		draw_fractol(t_frac *frac)
{
	put_fractol_to_image(frac);
	mlx_put_image_to_window(frac->mlx, frac->win, frac->img, 0, 0);
}
