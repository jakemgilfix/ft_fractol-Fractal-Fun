/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 18:42:49 by jgilfix           #+#    #+#             */
/*   Updated: 2020/02/13 12:59:53 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** EXIT_HOOK *******************************************************************
**   ~ This hook is called when the user presses [ESC] to terminate fdf.      **
********************************************************************************
*/

int	exit_hook(void *param)
{
	(void)param;
	exit(0);
}

/*
** KEY_PRESS_HOOK **************************************************************
**   ~ This hook handles user keypresses, taking the appropriate action       **
**     according to which key was pressed. Actions include:                   **
**       [ESC]    Exit Program                                                **
**       [ARROWS] Translate fractal in <direction>                            **
**       [R]      Reset default parameters                                    **
**       [1-4]    Change fractal (1: Mandelbrot, 2: Julia, etc.)              **
**       [+/-]    Change maximum iterations (and therefore colorset)          **
********************************************************************************
*/

int	key_press_hook(int key, void *param)
{
	const t_iterator	iterator[] = {&mandelbrot, &julia, &tricorn,
							&burning_ship, &cubic_julia, &mod_julia};
	t_frac				*frac;

	frac = (t_frac *)param;
	if (key == KEY_ESC)
		(void)exit_hook(param);
	if ((key == ARR_LEFT) || key == ARR_RIGHT)
		frac->orig.x += (key == ARR_RIGHT) ? 15 : -15;
	if ((key == ARR_UP) || key == ARR_DOWN)
		frac->orig.y += (key == ARR_UP) ? 15 : -15;
	if (key == KEY_R)
		reset_defaults(frac);
	if (key >= KEY_ONE && key <= KEY_FIVE)
	{
		frac->iter = iterator[key - KEY_ONE];
		reset_defaults(frac);
	}
	if ((key == KEY_PLUS || key == KEY_MINUS) && (frac->max_iter >= 20) &&
		(frac->max_iter <= 120))
		frac->max_iter += (key == KEY_PLUS) ? 5 : -5;
	draw_fractol(frac);
	return (0);
}

/*
** MOUSE_PRESS_HOOK ************************************************************
**   ~ This hook handles user mouse clicks, taking the appropriate action     **
**     according to which mouse button was clicked. Actions include:          **
**       [MOUSE1] Set fdf->mouse->is_pressed                                  **
**       [MWHEEL] Zoom in/out                                                 **
********************************************************************************
*/

int	mouse_press_hook(int button, int x, int y, void *param)
{
	t_frac	*frac;

	frac = (t_frac *)param;
	if (button == MWHEEL_UP && frac->zoom < (float)WIN_H * 55.0f)
	{
		frac->orig = (t_point){(frac->orig.x - x) * (frac->zoom * 1.2)
									/ frac->zoom + x,
								(frac->orig.y - y) * (frac->zoom * 1.2)
									/ frac->zoom + y};
		frac->zoom *= 1.2;
	}
	if (button == MWHEEL_DOWN && frac->zoom > 0.5f)
	{
		frac->orig = (t_point){(frac->orig.x - x) * (frac->zoom / 1.2)
									/ frac->zoom + x,
								(frac->orig.y - y) * (frac->zoom / 1.2)
									/ frac->zoom + y};
		frac->zoom /= 1.2;
	}
	draw_fractol(frac);
	return (0);
}

/*
** MOTION_HOOK *****************************************************************
**   ~ This hook handles user mouse movement. If MOUSE1 is pressed, tracks    **
**     the direction of mouse movement, allowing the user to rotate the       **
**     wireframe in the main window.                                          **
********************************************************************************
*/

int	motion_hook(int x, int y, void *param)
{
	t_frac	*frac;

	frac = (t_frac *)param;
	frac->c = (t_complex){(float)(x - frac->orig.x) / frac->zoom,
							(float)(y - frac->orig.y) / frac->zoom};
	draw_fractol(frac);
	return (0);
}
