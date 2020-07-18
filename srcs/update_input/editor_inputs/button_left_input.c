/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   button_left_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 08:54:33 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 22:09:21 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static bool	button_down_inputs(t_env *env)
{
	if (env->editor.state.section_state == EDITOR_SELECT_LINE)
	{
		if (!line_input(env))
			return (false);
	}
	else if (env->editor.state.section_state == EDITOR_SELECT_POINT)
		point_input(env);
	else if (env->editor.state.section_state == EDITOR_LEVELS
		&& (get_key(env->shortcuts.editor.level_point.start)
			|| get_key(env->shortcuts.editor.level_point.end)))
	{
		if (!level_input(env))
			return (false);
	}
	else if (env->editor.state.section_state == EDITOR_OBJECT)
	{
		if (!object_input(env))
			return (false);
	}
	env->need_redraw = true;
	return (true);
}

bool		button_left_input(t_env *env)
{
	if (get_button_down(SDL_BUTTON_LEFT, NULL))
		return (button_down_inputs(env));
	else if (env->editor.state.section_state == EDITOR_SELECT_POINT)
		return (drag_map_point_input(env));
	else if (env->editor.drag_point.point_is_dragged
		&& env->editor.state.section_state != EDITOR_SELECT_POINT)
		cancel_drag_input(env);
	return (true);
}
