/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_inputs.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/27 21:26:04 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 15:50:49 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

void	cancel_input(t_env *env)
{
	if ((get_key(SDL_SCANCODE_LCTRL)
		&& get_key_down(env->shortcuts.editor.major.cancel))
		|| get_key_down(SDL_SCANCODE_ESCAPE))
	{
		if (env->editor.state.global_state == EDITOR_MAKE_SECTOR)
		{
			env->editor.unique_id_vertices -= env->editor.tmp_vertices.total;
			--env->editor.unique_id_sectors;
			cancel_sector_record(env);
			free_tmp_vertices(env);
			free_tmp_sector(env);
			env->editor.state.global_state = EDITOR_IDLE;
			env->need_redraw = true;
		}
		else
			send_notify("No sector in progress.", 0xFF0000, env);
	}
}

bool	undo_redo_input(t_env *env)
{
	if (get_key(SDL_SCANCODE_LCTRL)
		&& get_key_down(env->shortcuts.editor.major.undo_redo))
	{
		if (get_key(SDL_SCANCODE_LSHIFT))
		{
			if (!redo_event(&env->editor.event_handler, env))
				return (false);
			display_events(env, 1);
		}
		else
		{
			if (!undo_event(&env->editor.event_handler, env))
				return (false);
			display_events(env, -1);
		}
		env->need_redraw = true;
	}
	return (true);
}
