/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_menu_p4.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 19:27:24 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 23:29:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	scroll_down(void *param)
{
	t_gui_levels_selection	*levels_selection;

	levels_selection = param;
	if (levels_selection->start + levels_selection->size < levels_selection->
		levels->total)
	{
		levels_selection->start++;
		levels_selection->component.need_redraw = true;
	}
	return (true);
}

bool		create_scroll_down_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->scroll_down_button = create_button((SDL_Rect){520, 510,
		30, 30}, 0x0, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_add_image(levels_menu->scroll_down_button,
		env->gui_image.down_arrow_30x30);
	if (!add_default_action(levels_menu->scroll_down_button->
		on_click, &(t_default_event){&scroll_down,
		levels_menu->levels_selection}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->scroll_down_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}

static bool	add_levels(void *param)
{
	t_gui_levels_selection	*levels_selection;
	t_doom_map				*map;
	char					buff[32];

	levels_selection = param;
	ft_snprintf(buff, sizeof(buff), "map %lu",
		levels_selection->levels->total + 1);
	if (!(map = create_map(buff)))
		return (false);
	if (vector_insert(levels_selection->levels,
		levels_selection->selected_index + 1, &map) == false)
	{
		free_map(map);
		return (false);
	}
	levels_selection->selected_index++;
	if (levels_selection->start + levels_selection->size
		<= levels_selection->selected_index)
		levels_selection->start++;
	levels_selection->component.need_redraw = true;
	return (trigger_gui_custom_event(levels_selection->on_selection_change,
		*(t_doom_map **)vector_get(levels_selection->levels,
		levels_selection->selected_index)));
}

bool		create_new_map_button(t_levels_menu *levels_menu, t_env *env)
{
	if (!(levels_menu->new_map_button = create_button((SDL_Rect){195, 550, 30,
		30}, 0x0, env->fonts.deja_vu_sans_momo_16)))
		return (destroy_level_menu(levels_menu));
	button_add_image(levels_menu->new_map_button, env->gui_image.plus_30x30);
	if (!add_default_action(levels_menu->new_map_button->
		on_click, &(t_default_event){&add_levels, levels_menu->
		levels_selection}))
		return (destroy_level_menu(levels_menu));
	if (!container_add(levels_menu->container, levels_menu->new_map_button))
		return (destroy_level_menu(levels_menu));
	return (true);
}
