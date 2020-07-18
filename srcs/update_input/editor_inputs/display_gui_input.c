/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_gui_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:48:56 by thboura           #+#    #+#             */
/*   Updated: 2020/04/15 17:35:28 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

void	display_gui_input(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.level_menu))
	{
		if (env->gui.status == GUI_LEVELS
			&& env->gui.window->component.is_visible)
			set_visible(&env->gui.window->component, false);
		else
		{
			set_visible(&env->gui.window->component, true);
			init_levels_menu(&env->gui.levels_menu, env);
		}
		env->need_redraw = true;
	}
}
