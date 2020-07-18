/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_win_menu.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:30:45 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 16:30:46 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static t_color	lerp_color(t_color a, t_color b, float t)
{
	t_u8	*tmp_a;
	t_u8	*tmp_b;
	t_u8	*tmp_ret;
	t_color	ret;

	tmp_a = (t_u8 *)&a;
	tmp_b = (t_u8 *)&b;
	tmp_ret = (t_u8 *)&ret;
	tmp_ret[3] = tmp_a[3] + (tmp_b[3] - tmp_a[3]) * t;
	tmp_ret[2] = tmp_a[2] + (tmp_b[2] - tmp_a[2]) * t;
	tmp_ret[1] = tmp_a[1] + (tmp_b[1] - tmp_a[1]) * t;
	tmp_ret[0] = tmp_a[0] + (tmp_b[0] - tmp_a[0]) * t;
	return (ret);
}

static void		set_label_color_internal(t_gui_label *label, float t)
{
	((t_u8 *)&label->color)[0] = 0xFF * t;
	label->need_redraw = true;
	label->component.need_redraw = true;
}

static void		set_button_color_internal(t_gui_button *button, float t)
{
	((t_u8 *)&button->label->color)[0] = 0xFF * t;
	button->label->need_redraw = true;
	button->label->component.need_redraw = true;
	button->component.need_redraw = true;
}

static void		draw_fade_effect(t_env *env)
{
	t_u32	*pixels;
	t_u32	*framebuffer;
	int		i;
	float	t;

	pixels = env->main_window->surface->pixels;
	framebuffer = env->framebuffer->pixels;
	i = 0;
	t = env->gui.win_menu.current_time / env->gui.win_menu.animation_time;
	if (t > 1)
		t = 1;
	while (i < env->main_window->surface->w * env->main_window->surface->h)
	{
		pixels[i] = lerp_color(framebuffer[i], 0x777777, t);
		++i;
	}
	env->main_window->force_redraw = true;
	set_label_color_internal(env->gui.win_menu.win_label, t);
	set_label_color_internal(env->gui.win_menu.time_label, t);
	set_button_color_internal(env->gui.win_menu.restart_button, t);
	set_button_color_internal(env->gui.win_menu.main_menu_button, t);
	set_button_color_internal(env->gui.win_menu.exit_button, t);
}

void			update_win_menu(t_env *env)
{
	if (!env->gui.win_menu.animation)
		return ;
	if (env->gui.win_menu.current_time < env->gui.win_menu.animation_time)
	{
		env->gui.win_menu.current_time += env->ph_context.frame_time;
		draw_fade_effect(env);
	}
	else
	{
		env->gui.win_menu.container->component.background = 0x777777FF;
		env->gui.win_menu.container->component.use_background = true;
		env->gui.win_menu.win_label->component.background = 0x777777FF;
		env->gui.win_menu.win_label->component.use_background = true;
		env->gui.win_menu.container->component.need_redraw = true;
		env->gui.win_menu.animation = false;
		env->main_window->force_redraw = true;
	}
}
