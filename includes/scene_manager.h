/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene_manager.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/10 17:56:23 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 15:32:47 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_MANAGER_H
# define SCENE_MANAGER_H

# include "libft.h"
# include <stdbool.h>
# include <stdlib.h>

typedef bool	(*t_scene_func)(void *);

typedef struct	s_scene
{
	t_scene_func	init;
	t_scene_func	draw;
	t_scene_func	update;
	t_scene_func	destroy;
	void			*param;
}				t_scene;

typedef enum	e_scene_action_type
{
	NO_ACTION,
	LOAD_SCENE,
	UNLOAD_SCENE
}				t_scene_action_type;

typedef struct	s_scene_action
{
	t_scene_action_type	type;
	t_scene				*scene;
}				t_scene_action;

typedef struct	s_scene_manager
{
	t_scene			*current_scene;
	t_scene_action	pending_action;
}				t_scene_manager;

t_scene_manager	*get_scene_manager(void);
t_scene			*get_current_scene(void);
void			free_scene_manager(void);
bool			update_scene_manager(void);
void			load_scene(t_scene *scene);
void			unload_current_scene(void);
t_scene			*create_scene(t_scene_func init, t_scene_func draw,
	t_scene_func update, t_scene_func destroy);
void			free_scene(t_scene **scene);
void			add_param_to_scene(t_scene *scene, void *param);

#endif
