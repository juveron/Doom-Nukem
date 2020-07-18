/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_p2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 18:55:46 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 19:17:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		create_levels_label(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->levels_label = create_label(vec2i(0, 10), 0xFFFFFFFF,
		env->fonts.deja_vu_sans_momo_16, 0x333333FF)))
		return (destroy_level_menu(levels_menu));
	if (!label_change_name(levels_menu->levels_label, "Levels menu"))
		return (destroy_level_menu(levels_menu));
	levels_menu->levels_label->component.rect.x = 300
		- levels_menu->levels_label->component.rect.w / 2;
	if (!container_add(levels_menu->container, levels_menu->levels_label))
		return (destroy_level_menu(levels_menu));
	return (true);
}

static bool	selection_change(void *tmp_map, void *param)
{
	t_doom_map		*map;
	t_levels_menu	*levels_menu;

	map = tmp_map;
	levels_menu = param;
	return (textfield_change_value(levels_menu->map_name_textfield, map->name));
}

bool		create_levels_selection_change(t_levels_menu *levels_menu,
	t_env *env)
{
	if (!(levels_menu->levels_selection = create_levels_selection((SDL_Rect)
		{15, 40, 500, 500}, &env->maps, env)))
		return (destroy_level_menu(levels_menu));
	if (!add_custom_action(levels_menu->
		levels_selection->on_selection_change, &(t_custom_event){
		selection_change, levels_menu}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->levels_selection))
		return (destroy_level_menu(levels_menu));
	return (true);
}

static bool	move_level_up(void *param)
{
	t_gui_levels_selection	*levels_selection;
	void					*tmp;
	t_doom_map				**maps;

	levels_selection = param;
	if (levels_selection->selected_index == 0)
		return (true);
	maps = levels_selection->levels->items;
	tmp = maps[levels_selection->selected_index];
	maps[levels_selection->selected_index] = maps[levels_selection->
		selected_index - 1];
	maps[levels_selection->selected_index - 1] = tmp;
	if (levels_selection->selected_index - 1 == *levels_selection->
		current_map_index)
		(*levels_selection->current_map_index)++;
	else if (levels_selection->selected_index == *levels_selection->
		current_map_index)
		(*levels_selection->current_map_index)--;
	levels_selection->selected_index--;
	levels_selection->component.need_redraw = true;
	return (true);
}

bool		create_move_up_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->move_up_button = create_button((SDL_Rect){115, 550, 30,
		30}, 0x0, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_add_image(levels_menu->move_up_button,
		env->gui_image.up_arrow_30x30);
	if (!add_default_action(levels_menu->move_up_button->
		on_click, &(t_default_event){&move_level_up, levels_menu->
		levels_selection}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->move_up_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}
