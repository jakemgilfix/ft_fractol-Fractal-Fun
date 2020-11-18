/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jgilfix <jgilfix@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 09:30:38 by jgilfix           #+#    #+#             */
/*   Updated: 2020/02/13 13:33:49 by jgilfix          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int	print_menu(char *filename)
{
	ft_printf("%{cyan}Usage\t\t%{magenta}:\t%{nocolor}%s <fractal_type>\n\n",
				filename);
	ft_printf("%{cyan}Options\t\t%{magenta}:\t%{nocolor}");
	ft_printf("1%{cyan})\t%{nocolor}Mandelbrot\n");
	ft_printf("\t\t\t2%{cyan})\t%{nocolor}Julia\n");
	ft_printf("\t\t\t3%{cyan})\t%{nocolor}Tricorn\n");
	ft_printf("\t\t\t4%{cyan})\t%{nocolor}Burning_Ship\n");
	ft_printf("\t\t\t5%{cyan})\t%{nocolor}Modified_Julia\n");
	ft_printf("\t\t\t6%{cyan})\t%{nocolor}Cubic_Julia\n\n");
	ft_printf("%{cyan}Key Bindings\t%{magenta}:");
	ft_printf("\t%{cyan}[%{nocolor}1-6%{cyan}]\t%{nocolor}Change fractal\n");
	ft_printf("\t\t\t%{cyan}[%{nocolor}+/-%{cyan}]%{nocolor}\t");
	ft_printf("Increase/Reduce maximum iterations AND change colors\n");
	ft_printf("\t\t\t%{cyan}[%{nocolor}R%{cyan}]%{nocolor}\t");
	ft_printf("Restore default settings\n");
	ft_printf("\t\t\t%{cyan}[%{nocolor}Arr%{cyan}]%{nocolor}\t");
	ft_printf("Translate fractal up/down/left/right\n");
	ft_printf("\t\t\t%{cyan}[%{nocolor}M3%{cyan}]%{nocolor}\t");
	ft_printf("(Mousewheel) Zoom in/out at mouse location\n");
	ft_printf("\t\t\t%{cyan}[%{nocolor}ESC%{cyan}]%{nocolor}\tQuit\n");
	exit(0);
	return (0);
}

static void	fractol_init(t_frac *frac, int frac_num)
{
	const t_iterator	iterator[] = {&mandelbrot, &julia, &tricorn,
							&burning_ship, &mod_julia, &cubic_julia};

	if (frac_num == -1)
		exit_hook(frac);
	frac->mlx = mlx_init();
	frac->win = mlx_new_window(frac->mlx, WIN_W, WIN_H, WIN_TITLE);
	frac->img = mlx_new_image(frac->mlx, WIN_W, WIN_H);
	frac->data = (int *)mlx_get_data_addr(frac->img, &(frac->bpp),
		&(frac->size_l), &(frac->endian));
	frac->iter = iterator[frac_num];
	reset_defaults(frac);
}

static int	get_fractol_index(char *name)
{
	int			i;
	const char	*fractals[] = {"Mandelbrot", "Julia", "Tricorn",
								"Burning_Ship", "Modified_Julia",
								"Cubic_Julia"};

	i = -1;
	while ((size_t)++i < (sizeof(fractals) / sizeof(*fractals)))
		if (!ft_strcmp(name, fractals[i]))
			return (i);
	return (-1);
}

static void	set_hooks(t_frac *frac)
{
	mlx_do_key_autorepeatoff(frac->mlx);
	mlx_hook(frac->win, 2, 0, key_press_hook, frac);
	mlx_hook(frac->win, 4, 0, mouse_press_hook, frac);
	mlx_hook(frac->win, 6, 0, motion_hook, frac);
	mlx_hook(frac->win, 17, 0, exit_hook, frac);
}

int			main(int ac, char **av)
{
	t_frac	frac;

	(ac != 2) && print_menu(av[0]);
	fractol_init(&frac, get_fractol_index(av[1]));
	draw_fractol(&frac);
	set_hooks(&frac);
	mlx_loop(frac.mlx);
}
