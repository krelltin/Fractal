/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/19 15:27:38 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/22 15:18:37 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>
#include <unistd.h>

int		fractol_color(t_env *e, int i)
{
	t_col	a;

	a.r = 0;
	a.g = 0;
	a.b = 0;
	(e->color_c == 0 && (i * 15 <= 255)) ? (a.r = i * 15) : 0;
	(e->color_c == 1 && (i * 15 <= 255)) ? (a.g = i * 15) : 0;
	(e->color_c == 2 && (i * 15 <= 255)) ? (a.b = i * 15) : 0;
	(e->color_c == 0 && (i * 15 > 255)) ? (a.r = 255) : 0;
	(e->color_c == 1 && (i * 15 > 255)) ? (a.g = 255) : 0;
	(e->color_c == 2 && (i * 15 > 255)) ? (a.b = 255) : 0;
	(e->color_c == 0 && (i * 15 <= 510)) ? (a.g = (i * 15) - 255) : 0;
	(e->color_c == 1 && (i * 15 <= 510)) ? (a.b = (i * 15) - 255) : 0;
	(e->color_c == 2 && (i * 15 <= 510)) ? (a.r = (i * 15) - 255) : 0;
	(e->color_c == 0 && (i * 15 > 510)) ? (a.g = 255) : 0;
	(e->color_c == 1 && (i * 15 > 510)) ? (a.b = 255) : 0;
	(e->color_c == 2 && (i * 15 > 510)) ? (a.r = 255) : 0;
	(e->color_c == 0 && (i * 15 > 510)) ? (a.b = ((i * 15) - 510)) : 0;
	(e->color_c == 1 && (i * 15 > 510)) ? (a.r = ((i * 15) - 510)) : 0;
	(e->color_c == 2 && (i * 15 > 510)) ? (a.g = ((i * 15) - 510)) : 0;
	return (((a.r & 0xFF) << 16) + ((a.g & 0xFF) << 8) + (a.b & 0xFF));
}

void	fractol_setup(t_env *e, t_inf *m, int *i)
{
	m->zx = ((e->type == 1 || e->type == 5 || e->type == 6) ?
		1.5 * (m->x - e->win_x / 2) / (0.2 * e->zoom * e->win_x) + e->move_x :
		(m->x - e->win_x / 2) / (0.2 * e->zoom * e->win_x) + e->move_x);
	m->zy = (m->y - e->win_y / 2) / (0.2 * e->zoom * e->win_y) + e->move_y;
	(e->type > 1 && e->type < 5) ? m->tmp_zx = m->zx : 0;
	(e->type > 1 && e->type < 5) ? m->tmp_zy = m->zy : 0;
	*i = 0;
}

void	fractol_type(char *av, t_env *e)
{
	if (!ft_strcmp("Julia", av))
		e->type = 1;
	else if (!ft_strcmp("Mandelbrot", av))
		e->type = 2;
	else if (!ft_strcmp("Tricorn", av))
		e->type = 3;
	else if (!ft_strcmp("Burning_Ship", av))
		e->type = 4;
	else if (!ft_strcmp("Glynn", av))
	{
		e->n = 1.1;
		e->type = 5;
	}
	else if (!ft_strcmp("Phoenix", av))
		e->type = 6;
	else
		fractol_error(1);
}

void	fractol_error(int i)
{
	if (i == 0)
	{
		ft_putstr("usage: ./fractol [name of fractal]\n");
		ft_putstr("       ./fractol [name of fractal] [name of fractal]\n\n");
		ft_putstr("fractal: [Julia] [Mandelbrot] [Tricorn]\n");
		ft_putstr("         [Burning_Ship] [Glynn] [Phoenix]\n\n");
	}
	else if (i == 1)
		ft_putstr("error: no such fractol\n");
	exit(0);
}

int		main(int ac, char **av)
{
	t_env		e;
	t_env		f;

	if (ac != 2 && ac != 3)
		fractol_error(0);
	ft_bzero(&e, sizeof(t_env));
	fractol_type(av[1], &e);
	e.win_x = 800;
	e.win_y = 800;
	e.m_i = 50;
	e.zoom = 1;
	if (ac == 3)
	{
		f = e;
		fractol_type(av[2], &f);
		if (!fork())
			fractol_win((void*)&f);
		else
			fractol_win((void*)&e);
	}
	else
		fractol_win((void*)&e);
	return (0);
}
