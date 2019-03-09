/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/13 15:27:59 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_putinfo(t_fract *f)
{
	mlx_string_put(f->mlx_ptr, f->win_ptr, WINSIZE - 200, WINSIZE - 20,
				0xffffff, "Press ESC to exit");
	if (f->set == 1)
		mlx_string_put(f->mlx_ptr, f->win_ptr, 10, WINSIZE - 100,
				0x33dd33, "Left click to magic");
	else
		mlx_string_put(f->mlx_ptr, f->win_ptr, 10, WINSIZE - 100,
				0x33dd33, "Left click to invert colors");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 10, WINSIZE - 80,
				0x33dd33, "Mouse scroll to zoom");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 10, WINSIZE - 60,
				0x33dd33, "Scroll click to center");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 10, WINSIZE - 40,
				0x33dd33, "Right click to show set");
	mlx_string_put(f->mlx_ptr, f->win_ptr, 10, WINSIZE - 20,
				0x33dd33, "Num+ and Num- to manage iterations");
}

void	fractol(t_fract *f)
{
	if (f->img.img_ptr)
		mlx_destroy_image(f->mlx_ptr, f->img.img_ptr);
	if (!(f->img.img_ptr = mlx_new_image(f->mlx_ptr, WINSIZE, WINSIZE)))
		ft_error(3, f);
	if (f->set == 0)
	{
		if (!(f->noinit))
			ft_mb_init(f);
		mb_pthread(f);
	}
	else if (f->set == 1)
	{
		if (!(f->noinit))
			ft_jl_init(f);
		jl_pthread(f);
	}
	else if (f->set == 2)
	{
		if (!(f->noinit))
			ft_tc_init(f);
		tc_pthread(f);
	}
	ft_putinfo(f);
}

int		argread(char *arg, t_fract *f)
{
	if (!(f = (t_fract *)malloc(sizeof(t_fract))))
		ft_error(2, f);
	f->img.img_ptr = NULL;
	f->win_ptr = NULL;
	f->mlx_ptr = NULL;
	if (!(f->mlx_ptr = mlx_init()))
		ft_error(3, f);
	f->noinit = 0;
	if (ft_strequ(arg, "mandelbrot") == 1)
		f->set = 0;
	else if (ft_strequ(arg, "julia") == 1)
		f->set = 1;
	else
		f->set = 2;
	fractol(f);
	mlx_key_hook(f->win_ptr, ft_key, (void *)f);
	mlx_mouse_hook(f->win_ptr, ft_mouse, (void *)f);
	if (f->set == 1)
		mlx_hook(f->win_ptr, 6, (1L << 6), mousemove, (void *)f);
	mlx_loop(f->mlx_ptr);
	return (1);
}

int		main(int argc, char **argv)
{
	t_fract	*f;

	f = NULL;
	if (argc == 2 && (ft_strequ(argv[1], "mandelbrot") ||
				ft_strequ(argv[1], "julia") || ft_strequ(argv[1], "tricorn")))
		argread(argv[1], f);
	else
		ft_error(1, f);
	return (0);
}
