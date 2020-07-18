/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   insert_input.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 21:29:19 by thboura           #+#    #+#             */
/*   Updated: 2020/04/15 17:36:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static bool	record_insertion(t_env *env)
{
	if (env->editor.closest != NULL)
	{
		if (recorded_insert_point(env))
			send_notify("Point successfully inserted.", 0xFFFFFF, env);
		else
		{
			send_notify("Failed to insert point.", 0XFF0000, env);
			return (false);
		}
	}
	else
		send_notify("No close wall.", 0xFF0000, env);
	return (true);
}

bool		insert_input(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.modify.insert))
	{
		get_dragged_point(env);
		if (env->editor.state.section_state == EDITOR_SELECT_POINT)
		{
			if (!env->editor.drag_point.point_is_dragged)
			{
				if (!record_insertion(env))
					return (false);
			}
			else
				send_notify("Point already used.", 0xFF0000, env);
			env->need_redraw = true;
		}
		env->editor.drag_point.point_is_dragged = false;
		env->editor.drag_point.dragged_point = NULL;
	}
	return (true);
}
