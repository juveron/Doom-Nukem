/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 21:31:45 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 21:48:34 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static bool	delete_sector_input(t_env *env, t_sector *test)
{
	if (verify_sector_in_levels(env, test))
		send_notify("You need to delete level points first.", 0xFF0000, env);
	else if (verify_objects_in_sector(env, test, false))
		send_notify("You need to delete pickup objects first.", 0xFF0000, env);
	else
	{
		if (env->gui.status == GUI_SECTOR && test == env->gui.sector_menu.
			sector)
		{
			send_notify("You need to delete sector menu first", 0xFF0000, env);
			return (true);
		}
		if (!delete_sector_event(env, test))
			return (false);
		ft_snprintf(env->buff, sizeof(env->buff), "Sector found: %lu",
			test->id);
		send_notify(env->buff, 0xFFFFFF, env);
		delete_sector(test, env);
	}
	return (true);
}

static bool	delete_point_input(t_env *env)
{
	t_sector	*test;
	int			ret;

	if (env->editor.drag_point.point_is_dragged)
	{
		ret = delete_point(env, env->editor.drag_point.dragged_point, true);
		env->editor.drag_point.dragged_point = NULL;
		env->editor.drag_point.point_is_dragged = false;
		if (ret == 1)
			send_notify("Point successfully deleted.", 0xFFFFFF, env);
		else if (ret == 0)
			send_notify("Deletion not possible.", 0xFFFFFF, env);
		else
			return (false);
	}
	else if ((test = is_in_sector(env, &(t_vec2f){env->editor.position_map.v.x,
		env->editor.position_map.v.z}, true)) != NULL)
	{
		if (!delete_sector_input(env, test))
			return (false);
	}
	else
		send_notify("No deletion possible", 0xFFFFFF, env);
	return (true);
}

static bool	delete_level_input(t_env *env)
{
	if (env->editor.drag_point.point_is_dragged)
		send_notify("This point isn't a level parameter.", 0xFF0000, env);
	else
	{
		if (!delete_level_point(env, get_level_point(&env->
			current_map->level, &env->editor.position_map.v), true))
			return (false);
	}
	return (true);
}

static bool	delete_object_input(t_env *env)
{
	if (env->editor.drag_point.point_is_dragged)
		send_notify("This point isn't an object.", 0xFF0000, env);
	else
	{
		if (delete_pickup_object(env, &env->editor.position_map.v, true) == 2)
			return (false);
	}
	return (true);
}

bool		delete_inputs(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.modify.delete))
	{
		get_dragged_point(env);
		if (env->editor.state.section_state == EDITOR_SELECT_POINT)
		{
			if (!delete_point_input(env))
				return (false);
		}
		else if (env->editor.state.section_state == EDITOR_LEVELS)
		{
			if (!delete_level_input(env))
				return (false);
		}
		else if (env->editor.state.section_state == EDITOR_OBJECT)
		{
			if (!delete_object_input(env))
				return (false);
		}
		env->need_redraw = true;
		env->editor.drag_point.point_is_dragged = false;
	}
	return (true);
}
