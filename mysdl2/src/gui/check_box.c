/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_box.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 17:52:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/12 03:20:51 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool				draw_check_box_func(void *param)
{
	t_gui_check_box	*check_box;

	check_box = param;
	draw_rectangle((SDL_Rect){1, 1, check_box->component.rect.w - 2,
		check_box->component.rect.h - 2}, check_box->color,
		check_box->component.surface);
	if (check_box->checked)
	{
		draw_line((t_vec2i){1, 1}, (t_vec2i){check_box->component.rect.w - 2,
			check_box->component.rect.h - 2}, 0xFFFFFFFF,
			check_box->component.surface);
		draw_line((t_vec2i){1, check_box->component.rect.h - 2},
			(t_vec2i){check_box->component.rect.w - 2, 1}, 0xFFFFFFFF,
			check_box->component.surface);
	}
	return (true);
}

void				check_box_enable(t_gui_check_box *check_box,
	bool enable)
{
	if (check_box->checked != enable)
	{
		check_box->checked = enable;
		check_box->component.need_redraw = true;
	}
}

bool				update_check_box_func(void *param)
{
	t_gui_check_box	*check_box;
	t_vec2i			pos;
	t_vec2i			mouse_pos;

	check_box = param;
	mouse_pos = get_mouse_position();
	pos = get_component_pos((t_component *)check_box);
	if (check_box->on_toggle->dlist_handler->size)
	{
		if (get_button_down(SDL_BUTTON_LEFT, NULL) && is_in_box(mouse_pos,
			&(SDL_Rect){pos.x, pos.y, check_box->component.rect.w,
			check_box->component.rect.h}))
		{
			check_box->checked ^= 1;
			check_box->component.need_redraw = true;
			trigger_gui_custom_event(check_box->on_toggle, &check_box->checked);
		}
	}
	return (true);
}

bool				destroy_check_box(t_gui_check_box **check_box)
{
	int	ret;

	ret = 0;
	if (*check_box == NULL)
		return (true);
	ret += !component_remove_from_parent(*check_box);
	destroy_event_handler((*check_box)->on_toggle);
	destroy_component(&(*check_box)->component);
	free(*check_box);
	*check_box = NULL;
	return (ret == 0);
}

t_gui_check_box		*create_check_box(const SDL_Rect rect,
	const t_color color)
{
	t_gui_check_box	*check_box;

	if (!(check_box = ft_memalloc(sizeof(t_gui_check_box))))
		return (NULL);
	if (!init_component(&check_box->component, &rect, true, 0xff))
	{
		destroy_check_box(&check_box);
		return (NULL);
	}
	check_box->component.elem_type = GUI_ELEM_CHECK_BOX;
	check_box->component.draw = &draw_check_box_func;
	check_box->component.update = &update_check_box_func;
	check_box->color = color;
	if (!(check_box->on_toggle = create_event_handler(CUSTOM_EVENT_TYPE)))
	{
		destroy_check_box(&check_box);
		return (NULL);
	}
	return (check_box);
}
