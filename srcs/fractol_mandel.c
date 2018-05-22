/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_mandel.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/22 14:34:31 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/22 14:41:30 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	*mandel(void *t)
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
				m.zy = 2 * m.zx * m.zy + m.tmp_zy;
				m.zx = m.xtmp + m.tmp_zx;
				i++;
			}
			if (i < e->m_i && i > 0)
				e->data[(m.y * (int)e->win_x) + m.x] = fractol_color(e, i);
		}
	}
	return (NULL);
}

void	*tricorn(void *t)
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
				m.zy = -2 * m.zx * m.zy + m.tmp_zy;
				m.zx = m.xtmp + m.tmp_zx;
				i++;
			}
			if (i < e->m_i && i > 0)
				e->data[(m.y * (int)e->win_x) + m.x] = fractol_color(e, i);
		}
	}
	return (NULL);
}

void	*burning(void *t)
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
				m.xtmp = m.zx * m.zx - m.zy * m.zy + m.tmp_zx;
				m.zy = fabs(2 * m.zx * m.zy) + m.tmp_zy;
				m.zx = fabs(m.xtmp);
				i++;
			}
			if (i < e->m_i && i > 0)
				e->data[(m.y * (int)e->win_x) + m.x] = fractol_color(e, i);
		}
	}
	return (NULL);
}
