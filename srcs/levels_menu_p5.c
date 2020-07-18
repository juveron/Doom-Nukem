/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_p5.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:38:20 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 19:56:52 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

bool		load_levels(void *param)
{
	t_levels_menu	*level_menu;

	level_menu = param;
	*level_menu->current_map = *(t_doom_map **)vector_get(level_menu->
		levels_selection->levels, level_menu->levels_selection->selected_index);
	*level_menu->levels_selection->current_map_index = level_menu->
		levels_selection->selected_index;
	level_menu->levels_selection->component.need_redraw = true;
	clear_event(level_menu->env);
	if (level_menu->env->editor.history.available)
		level_menu->env->editor.history.event_selection->component.
			need_redraw = true;
	return (true);
}

bool		create_load_level_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->load_map_button = create_button((SDL_Rect){235, 550, 90,
		30}, 0x777777FF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_change_name(levels_menu->load_map_button, "Load map");
	if (!add_default_action(levels_menu->load_map_button->
		on_click, &(t_default_event){&load_levels, levels_menu}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->load_map_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}

bool		create_map_name_label(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->map_name_label = create_label((t_vec2i){20, 600},
		0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF)))
		return (destroy_level_menu(levels_menu));
	if (!label_change_name(levels_menu->map_name_label, "Map name"))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->map_name_label))
		return (destroy_level_menu(levels_menu));
	return (true);
}

static bool	rename_map(void *text, void *param)
{
	t_gui_levels_selection	*levels_selection;
	t_doom_map				*map;

	levels_selection = param;
	map = *(t_doom_map **)vector_get(levels_selection->levels,
		levels_selection->selected_index);
	free(map->name);
	if (((char *)text)[0] == '\0')
	{
		if (!(map->name = ft_strdup("no name")))
			return (false);
	}
	else if (!(map->name = ft_strdup(text)))
		return (false);
	levels_selection->component.need_redraw = true;
	return (true);
}

bool		create_map_name_textfield(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->map_name_textfield = create_textfield((SDL_Rect){110,
		590, 170, 40}, 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	if (!textfield_change_limit(levels_menu->map_name_textfield, 15))
		return (destroy_level_menu(levels_menu));
	if (!textfield_change_default_text(levels_menu->map_name_textfield,
		"map name"))
		return (destroy_level_menu(levels_menu));
	if (!add_custom_action(levels_menu->map_name_textfield->
		on_text_change, &(t_custom_event){rename_map, levels_menu->
		levels_selection}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->map_name_textfield))
		return (destroy_level_menu(levels_menu));
	return (true);
}
