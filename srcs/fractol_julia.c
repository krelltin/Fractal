/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_julia.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:29:56 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/22 15:21:40 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	*glynn(void *t)
{
	VARI;
	e = (t_env*)t;
	ft_bzero(&m, sizeof(t_inf));
	m.y = e->min - 1;
	while (++m.y < e->max)
	{
		m.x = -1;
		while (++m.x < e->win_x)
		{
			fractol_setup(e, &m, &i);
			while ((m.zx * m.zx + m.zy * m.zy) < 4 && i < e->m_i)
			{
				m.xtmp = pow((m.zx * m.zx + m.zy * m.zy), (e->n / 2)) *
					cos(e->n * atan2(m.zy, m.zx));
				m.zy = pow((m.zx * m.zx + m.zy * m.zy), (e->n / 2)) *
					sin(e->n * atan2(m.zy, m.zx)) + e->c_y;
				m.zx = m.xtmp + e->c_x;
				i++;
			}
			if (i < e->m_i && i > 0)
				e->data[(m.y * (int)e->win_x) + m.x] = fractol_color(e, i);
		}
	}
	return (NULL);
}

void	*julia(void *t)
{
	VARI;
	e = (t_env*)t;
	ft_bzero(&m, sizeof(t_inf));
	m.y = e->min - 1;
	while (++m.y < e->max)
	{
		m.x = -1;
		while (++m.x < e->win_x)
		{
			fractol_setup(e, &m, &i);
			while ((m.zx * m.zx + m.zy * m.zy) < 4 && i < e->m_i)
			{
				m.xtmp = m.zx * m.zx - m.zy * m.zy;
				m.zy = 2 * m.zx * m.zy + e->c_y;
				m.zx = m.xtmp + e->c_x;
				i++;
			}
			if (i < e->m_i && i > 0)
				e->data[(m.y * (int)e->win_x) + m.x] = fractol_color(e, i);
		}
	}
	return (NULL);
}

void	fractol_draw_phoenix_s(t_env *e, t_inf *m, int *i)
{
	t_inf	m_tmp;

	fractol_setup(e, m, i);
	fractol_setup(e, &m_tmp, i);
	while ((m->zx * m->zx + m->zy * m->zy) < 4 && *i < e->m_i)
	{
		m->xtmp = m->zx * m->zx - m->zy * m->zy;
		m->zy = 2 * fabs(m->zx * m->zy) + (e->p * m_tmp.zy);
		m->zx = m->xtmp + e->c_x + (e->p * m_tmp.zx);
		*i += 1;
	}
}

void	*phoenix(void *t)
{
	VARI;
	e = (t_env*)t;
	ft_bzero(&m, sizeof(t_inf));
	m.y = e->min - 1;
	while (++m.y < e->max)
	{
		m.x = -1;
		while (++m.x < e->win_x)
		{
			fractol_draw_phoenix_s(e, &m, &i);
			if (i < e->m_i && i > 0)
				e->data[(m.y * (int)e->win_x) + m.x] = fractol_color(e, i);
		}
	}
	return (NULL);
}
