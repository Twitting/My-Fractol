/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   userinput.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/13 15:12:16 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	zoom(int button, int x, int y, t_fract *f)
{
	if (button == 4)
	{
		f->xx = (x / f->zoom + f->xx) - (x / (f->zoom * 1.3));
		f->yy = (y / f->zoom + f->yy) - (y / (f->zoom * 1.3));
		f->zoom *= 1.3;
		f->iternum++;
	}
	else
	{
		f->xx = (x / f->zoom + f->xx) - (x / (f->zoom / 1.3));
		f->yy = (y / f->zoom + f->yy) - (y / (f->zoom / 1.3));
		f->zoom /= 1.3;
		f->iternum--;
	}
	fractol(f);
}

void	mousethings(int button, int x, int y, t_fract *f)
{
	x = x + y;
	if (button == MOUSE_LB)
	{
		if (f->set == 1)
			f->jl_toggler == 0 ? f->jl_toggler++ : f->jl_toggler--;
		else
			f->inverter == 0 ? f->inverter++ : f->inverter--;
	}
	if (button == MOUSE_SB)
	{
		f->zoom = WINSIZE / 4;
		f->xx = f->set == 1 ? -2 : -2.5;
		f->yy = -2;
		f->iternum = ITERNUM;
	}
	if (button == MOUSE_RB)
		f->black == 0 ? f->black++ : f->black--;
	fractol(f);
}

int		ft_mouse(int button, int x, int y, void *f)
{
	if (button == 4 || button == 5)
		zoom(button, x, y, (t_fract *)f);
	if (button >= 1 && button <= 3)
		mousethings(button, x, y, (t_fract *)f);
	return (1);
}

int		ft_key(int key, void *f)
{
	if (key == KEY_LEFT)
		((t_fract *)f)->xx -= 30 / ((t_fract *)f)->zoom;
	else if (key == KEY_RIGHT)
		((t_fract *)f)->xx += 30 / ((t_fract *)f)->zoom;
	else if (key == KEY_UP)
		((t_fract *)f)->yy -= 30 / ((t_fract *)f)->zoom;
	else if (key == KEY_DOWN)
		((t_fract *)f)->yy += 30 / ((t_fract *)f)->zoom;
	else if (key == KEY_PLUS)
		((t_fract *)f)->iternum++;
	else if (key == KEY_MINUS)
		((t_fract *)f)->iternum--;
	else if (key == KEY_ESCAPE)
		exit(0);
	fractol((t_fract *)f);
	return (1);
}

int		mousemove(int x, int y, void *f)
{
	if (((t_fract *)f)->jl_toggler)
	{
		((t_fract *)f)->c_r = x;
		((t_fract *)f)->c_i = y;
		fractol((t_fract *)f);
	}
	return (1);
}
