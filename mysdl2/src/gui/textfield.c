/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 10:01:39 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 23:25:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textfield_internal.h"

static void		draw_textfield_func_p2(t_gui_textfield *textfield)
{
	draw_rectangle((SDL_Rect){0, 0, textfield->component.rect.w,
		textfield->component.rect.h}, textfield->component.background,
		textfield->component.surface);
	SDL_BlitSurface(textfield->surface, NULL,
		textfield->component.surface, &(SDL_Rect){10, 10, 0, 0});
	if (textfield->is_focus && textfield->cursor_visible)
	{
		if (textfield->text_size > 0)
			draw_line((t_vec2i){10 + textfield->surface->w, 10},
				(t_vec2i){10 + textfield->surface->w, 10
				+ textfield->surface->h}, textfield->text_color,
				textfield->component.surface);
		else
			draw_line((t_vec2i){10, 10},
				(t_vec2i){10, 10
				+ textfield->surface->h}, textfield->text_color,
				textfield->component.surface);
	}
}

bool			draw_textfield_func(void *param)
{
	t_gui_textfield	*textfield;

	textfield = param;
	if (textfield->need_redraw)
	{
		SDL_FreeSurface(textfield->surface);
		if (textfield->text_size > 0)
		{
			if (!(textfield->surface = text_surface(textfield->text,
				textfield->text_color, textfield->font)))
				return (false);
		}
		else
		{
			if (!(textfield->surface = text_surface(textfield->default_text,
				0xBBBBBBFF, textfield->font)))
				return (false);
		}
		textfield->need_redraw = false;
	}
	draw_textfield_func_p2(textfield);
	return (true);
}

t_gui_textfield	*create_textfield(const SDL_Rect rect, const t_color color,
	TTF_Font *font)
{
	t_gui_textfield	*textfield;

	if (!(textfield = ft_memalloc(sizeof(t_gui_textfield))))
		return (NULL);
	textfield->font = font;
	if (!init_component(&textfield->component, &rect, true, 0x666666FF)
		|| !(textfield->default_text = ft_strdup("default text"))
		|| !(textfield->surface = text_surface(textfield->default_text,
			0xBBBBBBFF, textfield->font))
		|| !(textfield->on_text_change = create_event_handler(
			CUSTOM_EVENT_TYPE)))
	{
		destroy_textfield(&textfield);
		return (NULL);
	}
	textfield->component.elem_type = GUI_ELEM_TEXTFIELD;
	textfield->component.draw = &draw_textfield_func;
	textfield->component.update = &update_textfield_func;
	textfield->text_color = color;
	textfield->text_size_limit = 40;
	clock_restart(&textfield->cursor_blink_timer);
	clock_restart(&textfield->backspace_timer);
	return (textfield);
}

bool			destroy_textfield(t_gui_textfield **textfield)
{
	int	ret;

	ret = 0;
	if (*textfield == NULL)
		return (true);
	ret += !component_remove_from_parent(*textfield);
	destroy_component(&(*textfield)->component);
	SDL_FreeSurface((*textfield)->surface);
	free((*textfield)->default_text);
	free((*textfield)->text);
	destroy_event_handler((*textfield)->on_text_change);
	free(*textfield);
	*textfield = NULL;
	return (ret == 0);
}
