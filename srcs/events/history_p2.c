/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_p2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:02:39 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 15:56:41 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"

static void				wheel_event(t_gui_event_selection *event_selection,
	t_vec2i pos, t_vec2i mouse_pos)
{
	t_s32	tmp;

	tmp = get_mouse_wheel();
	if (tmp != 0 && is_in_box(mouse_pos, &((SDL_Rect){pos.x, pos.y,
		event_selection->component.rect.w, event_selection->component.rect.h})))
	{
		if (event_selection->end + tmp <= event_selection->event_handler->
			event_list->size && (t_s64)event_selection->start + tmp >= 0
			&& event_selection->event_handler->event_list->
			size > event_selection->size)
		{
			event_selection->start += tmp;
			event_selection->end = event_selection->start + event_selection->
				size;
			event_selection->component.need_redraw = true;
		}
	}
}

static bool				update_event_selection_func_p2(
	t_gui_event_selection *event_selection, t_u64 tmp)
{
	if (!set_selected_event(event_selection, get_dlist_by_index(
		event_selection->event_handler->event_list, tmp), tmp))
		return (false);
	event_selection->component.need_redraw = true;
	event_selection->selected_index = tmp + 1;
	return (true);
}

static bool				update_event_selection_func(void *param)
{
	t_gui_event_selection	*event_selection;
	t_vec2i					pos;
	t_vec2i					mouse_pos;
	t_u64					tmp;

	event_selection = param;
	if (!event_selection->env->editor.history.window->is_over)
		return (true);
	pos = get_component_pos(&event_selection->component);
	mouse_pos = get_mouse_position();
	if (get_button_down(SDL_BUTTON_LEFT, NULL) && is_in_box(mouse_pos,
		&((SDL_Rect){pos.x, pos.y, event_selection->component.rect.w,
		event_selection->component.rect.h})))
	{
		tmp = (mouse_pos.y - pos.y) / 30 + event_selection->start;
		if (tmp < event_selection->event_handler->event_list->size
			&& tmp != event_selection->selected_index - 1)
			if (!update_event_selection_func_p2(event_selection, tmp))
				return (false);
	}
	wheel_event(event_selection, pos, mouse_pos);
	return (true);
}

t_gui_event_selection	*create_event_selection(t_env *env, SDL_Rect rect,
	t_recorded_event_handler *event_handler)
{
	t_gui_event_selection	*event_selection;

	if (!(event_selection = ft_memalloc(sizeof(t_gui_event_selection))))
		return (NULL);
	if (init_component(&event_selection->component, &rect, true,
		0x777777FF) == false)
	{
		free(event_selection);
		return (NULL);
	}
	event_selection->event_handler = event_handler;
	event_selection->component.elem_type = GUI_ELEM_CUSTOM;
	event_selection->component.draw = &draw_event_selection_func;
	event_selection->component.update = &update_event_selection_func;
	event_selection->size = rect.h / 30;
	event_selection->font = env->fonts.deja_vu_sans_momo_16;
	event_selection->end = event_selection->size;
	event_selection->selected_index = get_dlist_index(env->editor.
		event_handler.event_list, env->editor.event_handler
		.current_event) + 1;
	event_selection->env = env;
	return (event_selection);
}
