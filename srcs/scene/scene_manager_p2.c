/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:55:43 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/10 20:33:40 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_manager.h"

void			free_scene_manager(void)
{
	free(get_scene_manager());
}

t_scene			*get_current_scene(void)
{
	return (get_scene_manager()->current_scene);
}

void			load_scene(t_scene *scene)
{
	t_scene_manager	*scene_manager;

	scene_manager = get_scene_manager();
	scene_manager->pending_action.type = LOAD_SCENE;
	scene_manager->pending_action.scene = scene;
}

static bool		update_scene_manager_p2(const t_scene_manager *scene_manager)
{
	if (scene_manager->current_scene)
	{
		if (!scene_manager->current_scene->destroy(
			scene_manager->current_scene->param))
			return (false);
	}
	return (true);
}

bool			update_scene_manager(void)
{
	t_scene_manager	*scene_manager;

	scene_manager = get_scene_manager();
	if (scene_manager->pending_action.type == NO_ACTION)
		return (true);
	if (scene_manager->pending_action.type == LOAD_SCENE)
	{
		if (scene_manager->current_scene)
		{
			if (!scene_manager->current_scene->destroy(
				scene_manager->current_scene->param))
				return (false);
		}
		scene_manager->current_scene = scene_manager->pending_action.scene;
		if (!scene_manager->pending_action.scene->init(scene_manager->
			pending_action.scene->param))
			return (false);
	}
	else if (scene_manager->pending_action.type == UNLOAD_SCENE)
		if (!update_scene_manager_p2(scene_manager))
			return (false);
	scene_manager->pending_action.type = NO_ACTION;
	return (true);
}
