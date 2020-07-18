/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quit_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/20 16:17:51 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 16:27:15 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

void	quit_input(t_env *env)
{
	if (get_key_down(env->shortcuts.editor.quit))
	{
		if (env->editor.state.global_state != EDITOR_IDLE)
			send_notify("Finish all actions before leaving", 0XFF0000, env);
		else
			load_scene(env->scenes.main_menu);
	}
}
