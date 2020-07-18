/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_editor_inputs.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 10:14:28 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 18:02:46 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

bool	global_editor_inputs(t_env *env)
{
	if (!env->main_window->is_over)
		return (true);
	quit_input(env);
	if (!change_mode_input(env))
		return (false);
	cancel_input(env);
	if (!undo_redo_input(env))
		return (false);
	if (!insert_input(env))
		return (false);
	if (!delete_inputs(env))
		return (false);
	if (!button_left_input(env))
		return (false);
	update_rotation_start(env);
	button_right_input(env);
	display_gui_input(env);
	if (!set_history(env, &env->editor.history))
		return (false);
	if (!save_map_input(env))
		return (false);
	if (!game_input(env))
		return (false);
	return (true);
}
