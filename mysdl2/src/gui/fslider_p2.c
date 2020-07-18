/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fslider_p2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/04/06 16:21:46 by kguibout          #+#    #+#             */
/*   Updated: 2020/04/07 16:12:55 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void			fslider_change_bar_color(t_gui_fslider *slider, t_color color)
{
	if (slider->bar_color != color)
	{
		slider->bar_color = color;
		slider->component.need_redraw = true;
	}
}

void			fslider_change_cursor_color(t_gui_fslider *slider,
	t_color color)
{
	if (slider->cursor_color != color)
	{
		slider->cursor_color = color;
		slider->component.need_redraw = true;
	}
}

float			fslider_get_value(t_gui_fslider *slider)
{
	return (slider->value);
}

void			fslider_set_percent_value(t_gui_fslider *slider, float t)
{
	slider->t = clampf(t, 0, 1);
	slider->value = lerpf(slider->min_value, slider->max_value, slider->t);
	slider->pos = lerpi(slider->pixel_min, slider->pixel_max, slider->t);
	trigger_gui_custom_event(slider->on_value_change, &slider->value);
	slider->component.need_redraw = true;
}

void			fslider_set_value(t_gui_fslider *slider, float value)
{
	value = clampf(value, slider->min_value, slider->max_value);
	slider->t = (float)(value - slider->pixel_min)
		/ (float)(slider->pixel_max - slider->pixel_min);
	slider->value = value;
	slider->pos = lerpi(slider->pixel_min, slider->pixel_max, slider->t);
	slider->component.need_redraw = true;
}
