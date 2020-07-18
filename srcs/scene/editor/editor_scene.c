/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   editor_scene.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:07:28 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 10:39:04 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_manager.h"
#include "draw_editor_internal.h"

bool	init_editor(void *param)
{
	t_env *env;

	env = param;
	if (!change_all_sources_state(&env->sound_manager, SRC_REWIND)
		|| !init_menu(env))
		return (false);
	env->app_state = APP_EDITOR;
	return (true);
}

bool	destroy_editor(void *param)
{
	t_env	*env;
	int		ret;

	env = param;
	ret = 0;
	if (env->editor.state.global_state == EDITOR_MAKE_SECTOR)
	{
		free_tmp_sector(env);
		free_tmp_vertices(env);
	}
	ret += !destroy_history(&env->editor.history);
	ret += !destroy_menu(env);
	return (ret == 0);
}

t_scene	*create_editor_scene(t_env *env)
{
	t_scene	*editor;

	if (!(editor = create_scene(init_editor, draw_editor, update_editor,
		destroy_editor)))
		return (NULL);
	add_param_to_scene(editor, env);
	return (editor);
}
