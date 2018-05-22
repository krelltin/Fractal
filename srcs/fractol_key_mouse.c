/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_key_mouse.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:27:03 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/22 14:51:31 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		fractol_mouse(int mouse, int x, int y, t_env *e)
{
	(void)x;
	(void)y;
	if (mouse == 5 || mouse == 4)
	{
		e->move_x_tmp = ((2 * x - e->win_x) / (e->win_x / 2)) / e->zoom;
		e->move_y_tmp = ((2 * y - e->win_y) / (e->win_y / 2)) / e->zoom;
		if ((x >= 0 && x <= e->win_x) && (y >= 0 && y <= e->win_y))
		{
			e->move_x += (mouse == 5 ?
					e->move_x_tmp / 9.5 : -(e->move_x_tmp / 9.5));
			e->move_y += (mouse == 5 ?
					e->move_y_tmp / 9.5 : -(e->move_y_tmp / 9.5));
			e->zoom = (mouse == 5 ? e->zoom * 1.1 : e->zoom / 1.1);
		}
		fractol_draw(e);
		fractol_win_message(e, 0);
	}
	if (mouse == 1)
		e->mouse_stop = (e->mouse_stop == 1 ? 0 : 1);
	return (0);
}

int		fractol_julia_mouse(int x, int y, t_env *e)
{
	if ((x >= 0 && x <= e->win_x) && (y >= 0 && y <= e->win_y)
			&& e->mouse_stop == 0)
	{
		e->c_x = (x - (e->win_x / 2)) / (e->win_x / 2);
		e->c_y = ((e->win_y / 2) - y) / (e->win_y / 2);
		fractol_draw(e);
		fractol_win_message(e, 0);
	}
	return (0);
}

void	fractol_key_type_color(int key, t_env *e)
{
	if (key == 8)
	{
		if (e->color_c == 2)
			e->color_c = 0;
		else
			e->color_c += 1;
	}
	if (key == 12)
	{
		if (e->type == 6)
			e->type = 1;
		else if (e->type == 4)
		{
			e->type += 1;
			e->n = 1.1;
		}
		else
			e->type += 1;
	}
}

void	fractol_reset(t_env *e)
{
	int		tmp;

	tmp = e->type;
	e->zoom = 1;
	e->m_i = 50;
	move_x = 0;
	move_y = 0;
	e->n = 1.1;

int		fractol_key(int key, t_env *e)
{
	key == 53 ? exit(0) : 0;
	key == 69 ? e->zoom *= 1.1 : 0;
	key == 78 ? e->zoom /= 1.1 : 0;
	key == 116 ? e->m_i += 1 : 0;
	(key == 121 && e->m_i - 1 >= 0) ? e->m_i -= 1 : 0;
	key == 126 ? e->move_y += e->win_y * 0.00005 / e->zoom : 0;
	key == 125 ? e->move_y -= e->win_y * 0.00005 / e->zoom : 0;
	key == 123 ? e->move_x -= e->win_x * 0.00005 / e->zoom : 0;
	key == 124 ? e->move_x += e->win_x * 0.00005 / e->zoom : 0;
	(key == 0 && e->type == 5 && e->n - 0.1 > 1) ? e->n -= 0.1 : 0;
	(key == 1 && e->type == 5 && e->n + 0.1 < 2) ? e->n += 0.1 : 0;
	(key == 35 && e->type == 6) ? e->p += 0.1 : 0;
	(key == 31 && e->type == 6) ? e->p -= 0.1 : 0;
	key == 15 ? fractol_reset(e) : 0;
	fractol_key_type_color(key, e);
	fractol_draw(e);
	key == 49 ? fractol_win_message(e, key) : fractol_win_message(e, 0);
	return (0);
}
