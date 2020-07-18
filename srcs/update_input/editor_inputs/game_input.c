/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:58:54 by thboura           #+#    #+#             */
/*   Updated: 2020/06/26 17:44:01 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

bool	game_input(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.game_state))
	{
		set_visible(&env->gui.window->component, false);
		set_visible(&env->gui.texture_menu->window->component, false);
		destroy_history(&env->editor.history);
		if (init_editor_game_state(env) == false)
			return (false);
	}
	return (true);
}
