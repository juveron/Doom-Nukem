/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   snap_point.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:23:50 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 14:36:50 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	get_snap_point(t_env *env)
{
	int		tmp;
	int		tmp_;
	t_vec2i	mouse_pos;
	t_vec2i	drag_pos;

	if (env->main_window->is_focus == false || is_over_gui_window(env))
		return ;
	mouse_pos = get_mouse_position();
	env->editor.last_map_pos = env->editor.position_map.v;
	tmp = (mouse_pos.x - env->editor.begin.x) / env->editor.subdiv + 0.5f;
	drag_pos.x = tmp * env->editor.subdiv;
	tmp_ = (mouse_pos.y - env->editor.begin.y) / env->editor.subdiv + 0.5f;
	drag_pos.y = tmp_ * env->editor.subdiv;
	env->editor.position_map.v.x = tmp * (1.f / env->editor.div)
		- floorf(env->editor.offset.x) - 1.f;
	env->editor.position_map.v.z = tmp_ * (1.f / env->editor.div)
		- floorf(env->editor.offset.y) - 1.f;
	env->editor.position_map.v.y = 0;
	if (!vec3f_equal(&env->editor.last_map_pos, &env->editor.position_map.v))
		env->need_redraw = true;
}

void	draw_snap_point(t_env *env)
{
	t_vec2i	pos;

	pos = grid_to_win(&env->editor.position_map.v, env);
	draw_elipse(rect(pos.x, pos.y, 5, 5), 0x0000FF, env->main_window->surface);
}
