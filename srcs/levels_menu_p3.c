/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_p3.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:20:08 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 19:49:58 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	move_level_down(void *param)
{
	t_gui_levels_selection	*levels_selection;
	void					*tmp;
	t_doom_map				**maps;

	levels_selection = param;
	if (levels_selection->selected_index == levels_selection->levels->total - 1)
		return (true);
	maps = levels_selection->levels->items;
	tmp = maps[levels_selection->selected_index];
	maps[levels_selection->selected_index] = maps[levels_selection->
		selected_index + 1];
	maps[levels_selection->selected_index + 1] = tmp;
	if (levels_selection->selected_index + 1 == *levels_selection->
		current_map_index)
		(*levels_selection->current_map_index)--;
	else if (levels_selection->selected_index == *levels_selection->
		current_map_index)
		(*levels_selection->current_map_index)++;
	levels_selection->selected_index++;
	levels_selection->component.need_redraw = true;
	return (true);
}

bool		create_move_down_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->move_down_button = create_button((SDL_Rect){155, 550, 30,
		30}, 0x0, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_add_image(levels_menu->move_down_button,
		env->gui_image.down_arrow_30x30);
	if (!add_default_action(levels_menu->move_down_button->
		on_click, &(t_default_event){&move_level_down, levels_menu->
		levels_selection}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->move_down_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}

static bool	scroll_up(void *param)
{
	t_gui_levels_selection	*levels_selection;

	levels_selection = param;
	if (levels_selection->start == 0)
		return (true);
	levels_selection->start--;
	levels_selection->component.need_redraw = true;
	return (true);
}

bool		create_scroll_up_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->scroll_up_button = create_button((SDL_Rect){520, 40, 30,
		30}, 0x0, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_add_image(levels_menu->scroll_up_button,
		env->gui_image.up_arrow_30x30);
	if (!add_default_action(levels_menu->scroll_up_button->
		on_click, &(t_default_event){&scroll_up,
		levels_menu->levels_selection}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->scroll_up_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}
