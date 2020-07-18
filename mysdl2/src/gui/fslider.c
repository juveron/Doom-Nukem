/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fslider.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 12:07:22 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/12 02:58:33 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"
#include "mysdl2.h"

bool			draw_fslider_func(void *param)
{
	t_gui_fslider	*slider;
	size_t			radius;
	size_t			cursor_radius;

	slider = param;
	radius = slider->component.rect.h / 4;
	cursor_radius = slider->component.rect.h / 2;
	draw_rectangle((SDL_Rect){cursor_radius, radius, slider->component.rect.w
		- radius * 4, radius * 2}, slider->bar_color,
		slider->component.surface);
	draw_elipse((SDL_Rect){cursor_radius, radius * 2, radius, radius},
		slider->bar_color, slider->component.surface);
	draw_elipse((SDL_Rect){slider->component.rect.w - cursor_radius, radius * 2,
		radius, radius}, slider->bar_color, slider->component.surface);
	draw_elipse((SDL_Rect){clampi(slider->pos, slider->pixel_min,
		slider->pixel_max), radius * 2, cursor_radius, cursor_radius},
		slider->cursor_color, slider->component.surface);
	return (true);
}

void			update_fslider_func_p2(t_gui_fslider *slider,
	t_vec2i *mouse_pos, t_vec2i *pos)
{
	int tmp;

	tmp = clampi(mouse_pos->x - pos->x, slider->pixel_min, slider->pixel_max);
	if (tmp != slider->pos)
	{
		slider->pos = tmp;
		slider->component.need_redraw = true;
		slider->t = (float)(tmp - slider->pixel_min)
			/ (float)(slider->pixel_max - slider->pixel_min);
		slider->value = lerpf(slider->min_value, slider->max_value,
			slider->t);
		trigger_gui_custom_event(slider->on_value_change, &slider->value);
	}
}

bool			update_fslider_func(void *param)
{
	t_gui_fslider	*slider;
	t_vec2i			mouse_pos;
	t_vec2i			pos;

	slider = param;
	mouse_pos = get_mouse_position();
	pos = get_component_pos(&slider->component);
	if (slider->is_clicked == false && get_button_down(SDL_BUTTON_LEFT, NULL)
		&& is_in_box(mouse_pos, &(SDL_Rect){pos.x, pos.y,
		slider->component.rect.w, slider->component.rect.h}))
		slider->is_clicked = true;
	if (slider->is_clicked == true)
		update_fslider_func_p2(slider, &mouse_pos, &pos);
	if (slider->is_clicked == true && get_button(SDL_BUTTON_LEFT,
		NULL) == false)
		slider->is_clicked = false;
	return (true);
}

bool			destroy_fslider(t_gui_fslider **slider)
{
	int	ret;

	ret = 0;
	if (*slider == NULL)
		return (true);
	destroy_event_handler((*slider)->on_value_change);
	destroy_component(&(*slider)->component);
	ret += !component_remove_from_parent(*slider);
	free(*slider);
	*slider = NULL;
	return (ret == 0);
}

t_gui_fslider	*create_fslider(const SDL_Rect rect, const float min,
	const float max)
{
	t_gui_fslider	*slider;

	if (!(slider = ft_memalloc(sizeof(t_gui_fslider))))
		return (NULL);
	if (!init_component(&slider->component, &rect, false, 0)
		|| !(slider->on_value_change = create_event_handler(CUSTOM_EVENT_TYPE)))
	{
		destroy_fslider(&slider);
		return (NULL);
	}
	slider->bar_color = 0xAAAAAAFF;
	slider->cursor_color = 0x222222FF;
	slider->component.draw = draw_fslider_func;
	slider->component.update = update_fslider_func;
	slider->pixel_min = slider->component.rect.h / 2;
	slider->pixel_max = slider->component.rect.w - slider->component.rect.h / 2;
	slider->min_value = min;
	slider->max_value = max;
	slider->t = 0;
	slider->value = min;
	return (slider);
}
