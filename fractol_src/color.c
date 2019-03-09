/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   color.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/13 15:02:23 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	ft_error(int errnum, t_fract *f)
{
	if (errnum == 1)
		write(1, "Usage: ./fractol [fractal name]\nfractals:\n\t\
mandelbrot\n\tjulia\n\ttricorn\n", 70);
	if (errnum == 2)
		write(2, "Memory allocation is failed, aborting...\n", 41);
	if (errnum == 3)
	{
		write(2, "MinilibX initialization is failed, aborting...\n", 41);
		if (f->img.img_ptr != NULL)
			free(f->img.img_ptr);
		if (f->win_ptr != NULL)
			free(f->win_ptr);
		if (f->mlx_ptr != NULL)
			free(f->mlx_ptr);
		free(f);
	}
	if (errnum == 4)
		write(2, "POSIX Thread error, aborting...\n", 32);
	exit(errnum);
}

void	set_color(t_fract *f)
{
	float p;

	p = f->n * 1.0 / f->iternum;
	if (f->inverter > 0)
		p = 1.0 - p;
	if (p > 0 && p < 0.25)
		f->color = (int)(0x00ff0000 + (int)(0x0000ff00
					* p * 4.0) / 0x100 * 0x100);
	else if (p >= 0.25 && p < 0.5)
		f->color = (int)(0x00ffff00 - (int)(0x00ff0000
					* (p - 0.25) * 4.0) / 0x10000 * 0x10000);
	else if (p >= 0.5 && p < 0.75)
		f->color = (int)(0x0000ff00 + (int)(0x000000ff
					* (p - 0.5) * 4.0));
	else if (p >= 0.75)
		f->color = (int)(0x0000ffff - (int)(0x0000ff00
					* (p - 0.75) * 4.0) / 0x100 * 0x100);
	if (f->n == f->iternum)
	{
		if (f->black)
			f->color = 0;
		else
			f->color = f->inverter > 0 ? 0xff0000 : 0xff;
	}
}
