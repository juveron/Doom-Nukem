/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:55:43 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 15:20:01 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_manager.h"

t_scene_manager	*get_scene_manager(void)
{
	static t_scene_manager	*scene_manager;

	if (scene_manager == NULL)
		scene_manager = ft_memalloc(sizeof(t_scene_manager));
	return (scene_manager);
}

void			unload_current_scene(void)
{
	t_scene_manager	*scene_manager;

	scene_manager = get_scene_manager();
	scene_manager->pending_action.type = UNLOAD_SCENE;
}

t_scene			*create_scene(t_scene_func init, t_scene_func draw,
	t_scene_func update, t_scene_func destroy)
{
	t_scene	*scene;

	if (!(scene = ft_memalloc(sizeof(t_scene))))
		return (NULL);
	scene->init = init;
	scene->draw = draw;
	scene->destroy = destroy;
	scene->update = update;
	return (scene);
}

void			free_scene(t_scene **scene)
{
	free(*scene);
	*scene = NULL;
}

void			add_param_to_scene(t_scene *scene, void *param)
{
	scene->param = param;
}
