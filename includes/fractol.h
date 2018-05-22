/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:27:50 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/22 15:21:43 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "../lib/Libft/libft.h"
# include <math.h>
# include <mlx.h>
# include <pthread.h>
# include <stdio.h>
# define STR_P e->mlx_ptr, e->win_ptr
# define VARI int i; t_inf m; t_env *e;

typedef struct		s_env
{
	void			*mlx_ptr;
	void			*win_ptr;
	void			*img_ptr;
	int				bpp;
	int				size_line;
	int				endian;
	int				*data;
	int				type;

	double			win_x;
	double			win_y;
	int				m_i;
	double			zoom;
	double			move_x;
	double			move_y;
	double			move_x_tmp;
	double			move_y_tmp;
	double			p;
	int				mouse_stop;

	double			n;
	double			c_x;
	double			c_y;
	int				color_c;
	int				max;
	int				min;
	int				menu;
}					t_env;

typedef struct		s_inf
{
	double			zx;
	double			zy;
	double			xtmp;
	double			tmp_zx;
	double			tmp_zy;
	int				x;
	int				y;
}					t_inf;

typedef struct		s_col
{
	int				r;
	int				g;
	int				b;
	int				track;
}					t_col;

/*
** main.c
*/
int					main(int ac, char **av);
void				fractol_error(int i);
void				fractol_type(char *av, t_env *e);
void				fractol_setup(t_env *e, t_inf *m, int *i);
int					fractol_color(t_env *e, int i);

/*
** julia.c
*/
void				*phoenix(void *t);
void				fractol_draw_phoenix_s(t_env *e, t_inf *m, int *i);
void				*julia(void *t);
void				*glynn(void *t);

/*
** key_mouse.c
*/
int					fractol_key(int key, t_env *e);
void				fractol_reset(t_env *e);
void				fractol_key_type_color(int key, t_env *e);
int					fractol_julia_mouse(int x, int y, t_env *e);
int					fractol_mouse(int mouse, int x, int y, t_env *e);

/*
** functions.c
*/
void				*fractol_win(void *t);
void				fractol_draw(t_env *e);
void				fractol_win_message(t_env *e, int key);
void				fractol_win_message_s(t_env *e);

/*
** mandel.c
*/
void				*burning(void *t);
void				*tricorn(void *t);
void				*mandel(void *t);
#endif
