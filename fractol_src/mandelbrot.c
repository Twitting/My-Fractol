/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mandelbrot.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/13 15:09:33 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	mandelbrot2(t_fract *f)
{
	f->c_r = 1.0 * f->x / f->zoom + f->xx;
	f->c_i = 1.0 * f->y / f->zoom + f->yy;
	f->a_r = 0;
	f->a_i = 0;
	f->n = 0;
	while (f->n < f->iternum && f->a_r * f->a_r + f->a_i * f->a_i < 4)
	{
		f->b_r = 1.0 * (f->a_r * f->a_r - f->a_i * f->a_i);
		f->b_i = 2.0 * f->a_r * f->a_i;
		f->a_r = 1.0 * (f->b_r + f->c_r);
		f->a_i = 1.0 * (f->b_i + f->c_i);
		f->n++;
	}
	set_color(f);
	f->img.data[f->y * WINSIZE + f->x] = f->color;
}

t_fract	*ft_mb_init(t_fract *f)
{
	f->noinit = 1;
	if (!(f->win_ptr = mlx_new_window(f->mlx_ptr, WINSIZE,
					WINSIZE, "Mandelbrot set")))
		ft_error(3, f);
	if (!(f->img.img_ptr = mlx_new_image(f->mlx_ptr, WINSIZE, WINSIZE)))
		ft_error(3, f);
	f->img.data = (int *)mlx_get_data_addr(f->img.img_ptr, &f->img.bpp,
			&f->img.size_l, &f->img.endian);
	f->zoom = WINSIZE / 4;
	f->xx = -2.5;
	f->yy = -2;
	f->inverter = 1;
	f->black = 1;
	f->iternum = ITERNUM;
	return (f);
}

void	*mandelbrot(void *f)
{
	while (((t_fract *)f)->y < ((t_fract *)f)->y_max)
	{
		((t_fract *)f)->x = 0;
		while (((t_fract *)f)->x < WINSIZE)
		{
			mandelbrot2((t_fract *)f);
			((t_fract *)f)->x++;
		}
		((t_fract *)f)->y++;
	}
	return (f);
}

void	mb_pthread(t_fract *f)
{
	pthread_t	thread[THREADS];
	t_fract		fract[THREADS];
	int			i;

	i = 0;
	while (i < THREADS)
	{
		ft_memcpy((void *)(&fract[i]), (void *)f, sizeof(t_fract));
		fract[i].y = THREAD_HEIGHT * i;
		fract[i].y_max = THREAD_HEIGHT * (i + 1);
		if (pthread_create(&thread[i], NULL, mandelbrot, &fract[i]) != 0)
			ft_error(4, f);
		i++;
	}
	while (i--)
		pthread_join(thread[i], NULL);
	mlx_put_image_to_window(f->mlx_ptr, f->win_ptr, f->img.img_ptr, 0, 0);
}
