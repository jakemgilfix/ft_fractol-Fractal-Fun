/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:30:54 by jgilfix           #+#    #+#             */
/*   Updated: 2020/02/13 13:11:45 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** BONUSES IMPLEMENTED *********************************************************
** 1) Zoom follows mouse position.                                            **
** 2) Use arrow keys to translate fractal position.                           **
** 3) Multi-threading (4 separate threads)                                    **
** 4) Twice the required number of fractals                                   **
** 5) Use '+'/'-' keys to inc./dec. maximum iterations AND also color         **
********************************************************************************
*/

#ifndef FRACTOL_H
# define FRACTOL_H

# include "../libft/include/libft.h"
# include "../libft/include/ft_printf.h"
# include "../libmlx/mlx.h"

# include <stdbool.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include <math.h>

/*
** MLX-RELATED SETTINGS ========================================================
*/

# define WIN_TITLE		"fractol ~ jgilfix"
# define WIN_H			1200
# define WIN_W			1600

/*
** KEY MACROS ==================================================================
*/

# define MOUSE1			1
# define MOUSE2			2
# define MOUSE3			3
# define MWHEEL_UP		4
# define MWHEEL_DOWN	5

# define KEY_ONE		18
# define KEY_TWO		19
# define KEY_THREE		20
# define KEY_FOUR		21

# define KEY_FIVE		23
# define KEY_SIX		22

# define KEY_PLUS		24
# define KEY_MINUS		27

# define KEY_R			15

# define KEY_ESC		53

# define ARR_LEFT		123
# define ARR_RIGHT		124
# define ARR_UP			125
# define ARR_DOWN		126

/*
** DATA STRUCTURES =============================================================
*/

typedef struct	s_point
{
	int	x;
	int	y;
}				t_point;

typedef struct	s_complex
{
	float	re;
	float	im;
}				t_complex;

typedef struct	s_frac
{
	int			bpp;
	int			size_l;
	int			endian;
	int			*data;
	void		*mlx;
	void		*win;
	void		*img;
	int			(*iter)(int x, int y, struct s_frac *frac);
	t_point		orig;
	int			zoom;
	int			max_iter;
	t_complex	c;
}				t_frac;

typedef int		(*t_iterator)(int x, int y, t_frac *frac);

typedef	struct	s_thr_params
{
	t_frac	*frac;
	int		thread;
}				t_thr_params;

/*
** HOOKS.C =====================================================================
*/

int				key_press_hook(int key, void *param);
int				exit_hook(void *param);
int				mouse_press_hook(int button, int x, int y, void *param);
int				motion_hook(int x, int y, void *param);

/*
** DRAW.C ======================================================================
*/

void			reset_defaults(t_frac *frac);
int				colorize(int n, t_frac *frac);
void			draw_fractol(t_frac *frac);

/*
** ITERATOR.C ==================================================================
*/

int				mandelbrot(int x, int y, t_frac *frac);
int				julia(int x, int y, t_frac *frac);
int				tricorn(int x, int y, t_frac *frac);
int				burning_ship(int x, int y, t_frac *frac);
int				mod_julia(int x, int y, t_frac *frac);

/*
** ANOTHER_ITERATOR.C ==========================================================
*/

int				cubic_julia(int x, int y, t_frac *frac);

#endif
