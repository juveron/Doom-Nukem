/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 12:48:56 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/27 23:12:29 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "levels_menu_internal.h"

bool	destroy_level_menu(t_levels_menu *levels_menu)
{
	int	ret;

	ret = 0;
	ret += !destroy_textfield((void *)&levels_menu->file_name_textfield);
	ret += !destroy_label(&levels_menu->file_name_label);
	ret += !destroy_textfield((void *)&levels_menu->map_name_textfield);
	ret += !destroy_label(&levels_menu->map_name_label);
	ret += !destroy_button(&levels_menu->load_map_button);
	ret += !destroy_button(&levels_menu->delete_map_button);
	ret += !destroy_button(&levels_menu->new_map_button);
	ret += !destroy_button(&levels_menu->scroll_down_button);
	ret += !destroy_button(&levels_menu->scroll_up_button);
	ret += !destroy_button(&levels_menu->move_down_button);
	ret += !destroy_button(&levels_menu->move_up_button);
	ret += !destroy_levels_selection(&levels_menu->levels_selection);
	ret += !destroy_label(&levels_menu->levels_label);
	ret += !destroy_container(&levels_menu->container);
	return (ret == 0);
}

bool	create_levels_menu(t_levels_menu *levels_menu, t_env *env)
{
	levels_menu->env = env;
	levels_menu->current_map = &env->current_map;
	levels_menu->start_object = env->levels_manager.start_obj;
	levels_menu->end_object = env->levels_manager.end_obj;
	if (!(levels_menu->container = create_container((SDL_Rect){0, 0, 600, 700},
		false, 0)))
		return (false);
	if (!create_levels_label(levels_menu, env)
		|| !create_levels_selection_change(levels_menu, env)
		|| !create_move_up_button(levels_menu, env)
		|| !create_move_down_button(levels_menu, env)
		|| !create_scroll_up_button(levels_menu, env)
		|| !create_scroll_down_button(levels_menu, env)
		|| !create_new_map_button(levels_menu, env)
		|| !create_load_level_button(levels_menu, env)
		|| !create_delete_level_button(levels_menu, env)
		|| !create_map_name_label(levels_menu, env)
		|| !create_map_name_textfield(levels_menu, env)
		|| !create_file_name_label(levels_menu, env)
		|| !create_file_name_textfield(levels_menu, env))
		return (false);
	return (true);
}

void	init_levels_menu(t_levels_menu *levels_menu, t_env *env)
{
	t_doom_map	*map;

	if (env->gui.status != GUI_LEVELS)
	{
		container_clear(env->gui.window->container);
		container_add(env->gui.window->container,
			&levels_menu->container->component);
		env->gui.window->container->component.need_redraw = true;
	}
	env->gui.status = GUI_LEVELS;
	levels_menu->levels_selection->selected_index = *levels_menu->
		levels_selection->current_map_index;
	map = *(t_doom_map **)vector_get(&env->maps,
		levels_menu->levels_selection->selected_index);
	textfield_change_value(levels_menu->map_name_textfield, map->name);
	textfield_change_value(levels_menu->file_name_textfield,
		env->map_file.file_name);
}
