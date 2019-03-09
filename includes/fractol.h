/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: twitting <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/21 14:55:36 by twitting          #+#    #+#             */
/*   Updated: 2019/02/13 15:14:19 by twitting         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "../libft/libft.h"
# include "mlx.h"

# define WINSIZE 900
# define ITERNUM 50
# define KEY_UP 126
# define KEY_DOWN 125
# define KEY_LEFT 123
# define KEY_RIGHT 124
# define KEY_PLUS 69
# define KEY_MINUS 78
# define KEY_ESCAPE 53
# define MOUSE_LB 1
# define MOUSE_RB 2
# define MOUSE_SB 3
# define THREADS 4
# define THREAD_HEIGHT (WINSIZE / THREADS)

typedef struct	s_img
{
	void		*img_ptr;
	int			*data;
	int			size_l;
	int			bpp;
	int			endian;
}				t_img;

typedef struct	s_fract
{
	void		*mlx_ptr;
	void		*win_ptr;
	t_img		img;
	int			n;
	double		a_r;
	double		a_i;
	double		b_r;
	double		b_i;
	double		c_r;
	double		c_i;
	double		d_r;
	double		d_i;
	double		xx;
	double		yy;
	int			x;
	int			y;
	int			y_max;
	int			color;
	double		zoom;
	int			iternum;
	int			inverter;
	int			black;
	int			set;
	int			noinit;
	int			jl_toggler;
}				t_fract;

void			ft_error(int errnum, t_fract *f);
void			set_color(t_fract *f);
void			fractol(t_fract *f);
int				mousemove(int x, int y, void *f);
t_fract			*ft_tc_init(t_fract *f);
void			tc_pthread(t_fract *f);
t_fract			*ft_jl_init(t_fract *f);
void			jl_pthread(t_fract *f);
t_fract			*ft_mb_init(t_fract *f);
void			mb_pthread(t_fract *f);
int				ft_mouse(int button, int x, int y, void *f);
int				ft_key(int key, void *f);

#endif
