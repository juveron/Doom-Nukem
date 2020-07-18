/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_mode_inputs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 21:19:16 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 18:05:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static bool	change_mode_available(t_env *env)
{
	if (env->editor.state.global_state == EDITOR_MAKE_SECTOR)
	{
		send_notify("You need to close all sectors.", 0xFF0000, env);
		return (false);
	}
	return (true);
}

bool		change_mode_input(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.mode.level))
	{
		if (change_mode_available(env))
		{
			if (!change_selection_mode(env, EDITOR_LEVELS))
				return (false);
			env->levels_manager.editor.active = true;
		}
	}
	if (get_key_down(env->shortcuts.editor.mode.point))
	{
		if (change_mode_available(env))
			return (change_selection_mode(env, EDITOR_SELECT_POINT));
	}
	if (get_key_down(env->shortcuts.editor.mode.line))
	{
		if (change_mode_available(env))
			return (change_selection_mode(env, EDITOR_SELECT_LINE));
	}
	if (get_key_down(env->shortcuts.editor.mode.object))
	{
		if (change_mode_available(env))
			return (change_selection_mode(env, EDITOR_OBJECT));
	}
	return (true);
}
