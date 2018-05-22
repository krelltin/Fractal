/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol_functions.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mhwangbo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:29:30 by mhwangbo          #+#    #+#             */
/*   Updated: 2018/05/22 15:22:28 by mhwangbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"
#include <stdio.h>

void	fractol_win_message_s(t_env *e)
{
	(e->type == 5) ?
		mlx_string_put(STR_P, 15, 165, 0xFFFFFF, "[A]/[S] : Change n") : 0;
	(e->type == 6) ?
		mlx_string_put(STR_P, 15, 165, 0xFFFFFF, "[P]/[O] : Change n") : 0;
	mlx_string_put(STR_P, 15, 145, 0xFFFFFF, "[R] : Reset");
	mlx_string_put(STR_P, e->win_x - 110, e->win_y - 85, 0xFFFFFF,
			"MOUSE GUIDE");
	mlx_string_put(STR_P, e->win_x - 160, e->win_y - 65, 0xFFFFFF,
			"[SCROLL] : zoom");
	(e->type == 1 || e->type > 4) ? mlx_string_put(STR_P,
		e->win_x - 220, e->win_y - 45, 0xFFFFFF, "[LEFT CLICK] : freeze") : 0;
}

void	fractol_win_message(t_env *e, int key)
{
	if (e->menu == 0 && key == 49)
		e->menu = 1;
	else if (e->menu == 1 && key == 49)
		e->menu = 0;
	if (e->menu == 1)
	{
		mlx_string_put(STR_P, 5, 5, 0xFFFFFF, "KEYBOARD GUIDE");
		mlx_string_put(STR_P, 15, 25, 0xFFFFFF, "[ESC] : exit");
		mlx_string_put(STR_P, 15, 45, 0xFFFFFF, "[+]/[-] : zoom");
		mlx_string_put(STR_P, 15, 65, 0xFFFFFF, "[ARROW] : move");
		mlx_string_put(STR_P, 15, 85, 0xFFFFFF, "[PAGE UP/DOWN] : iteration");
		mlx_string_put(STR_P, 15, 105, 0xFFFFFF, "[C] : color");
		mlx_string_put(STR_P, 15, 125, 0xFFFFFF, "[Q] : next fractal");
		mlx_string_put(STR_P, 15, 185, 0xFFFFFF, "[SPACE] : hide");
		fractol_win_message_s(e);
	}
	else if (e->menu == 0)
		mlx_string_put(STR_P, 5, 5, 0xFFFFFF, "[SPACE] : help");
}

void	fractol_draw(t_env *e)
{
	int			i;
	pthread_t	pid[5];
	t_env		t[5];

	i = -1;
	ft_bzero(e->data, e->win_x * e->win_y * 4);
	while (++i < 5 && ft_memcpy((void*)&t[i], e, sizeof(t_env)))
	{
		t[i].min = i * (e->win_x / 5);
		t[i].max = (i + 1) * (e->win_x / 5);
	}
	i = -1;
	while (++i < 5)
	{
		e->type == 1 ? pthread_create(&pid[i], NULL, julia, &t[i]) : 0;
		e->type == 2 ? pthread_create(&pid[i], NULL, mandel, &t[i]) : 0;
		e->type == 3 ? pthread_create(&pid[i], NULL, tricorn, &t[i]) : 0;
		e->type == 4 ? pthread_create(&pid[i], NULL, burning, &t[i]) : 0;
		e->type == 5 ? pthread_create(&pid[i], NULL, glynn, &t[i]) : 0;
		e->type == 6 ? pthread_create(&pid[i], NULL, phoenix, &t[i]) : 0;
	}
	while (--i >= 0)
		pthread_join(pid[i], NULL);
	mlx_put_image_to_window(e->mlx_ptr, e->win_ptr, e->img_ptr, 0, 0);
}

void	*fractol_win(void *t)
{
	t_env *e;

	e = (t_env*)t;
	e->mlx_ptr = mlx_init();
	e->win_ptr = mlx_new_window(e->mlx_ptr, e->win_x, e->win_y, "fractol");
	e->img_ptr = mlx_new_image(e->mlx_ptr, e->win_x, e->win_y);
	e->data = (int*)mlx_get_data_addr(e->img_ptr, &e->bpp, &e->size_line,
			&e->endian);
	fractol_draw(e);
	fractol_win_message(e, 0);
	mlx_mouse_hook(e->win_ptr, fractol_mouse, e);
	(e->type == 1 || e->type == 5 || e->type == 6) ?
		mlx_hook(e->win_ptr, 6, 2, fractol_julia_mouse, e) : 0;
	mlx_hook(e->win_ptr, 2, 2, fractol_key, e);
	mlx_loop(e->mlx_ptr);
	return (NULL);
}
