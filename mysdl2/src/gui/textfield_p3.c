/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield_p3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:01:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/01 15:01:33 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

static bool	backspace(t_gui_textfield *textfield)
{
	char	*tmp;

	clock_restart(&textfield->backspace_timer);
	if (!(tmp = ft_strsub(textfield->text, 0, textfield->text_size - 1)))
		return (false);
	free(textfield->text);
	textfield->text = tmp;
	textfield->text_size--;
	textfield->need_redraw = true;
	textfield->component.need_redraw = true;
	return (true);
}

static void	blink_cursor(t_gui_textfield *textfield)
{
	textfield->cursor_visible ^= 1;
	clock_restart(&textfield->cursor_blink_timer);
	textfield->component.need_redraw = true;
}

static bool	update_textfield_func_p3(t_gui_textfield *textfield)
{
	if (!(textfield->text = ft_strljoin_free(textfield->text, get_textinput(),
			1, textfield->text_size_limit + 1)))
		return (false);
	textfield->text_size += ft_strlen(get_textinput());
	if (textfield->text_size > textfield->text_size_limit)
		textfield->text_size = textfield->text_size_limit;
	textfield->cursor_pos = textfield->text_size;
	textfield->need_redraw = true;
	textfield->component.need_redraw = true;
	return (true);
}

static bool	update_textfield_func_p2(t_gui_textfield *textfield)
{
	if (textfield->text_size > 0 && get_key(SDL_SCANCODE_BACKSPACE)
		&& clock_get_milliseconds(&textfield->backspace_timer) > 100)
		if (!backspace(textfield))
			return (false);
	if (textfield->text_size != textfield->text_size_limit
		&& get_textinput()[0] != '\0')
		if (!update_textfield_func_p3(textfield))
			return (false);
	if (clock_get_milliseconds(&textfield->cursor_blink_timer) > 500)
		blink_cursor(textfield);
	if (get_key_down(SDL_SCANCODE_RETURN))
	{
		textfield->is_focus = false;
		textfield->component.need_redraw = true;
	}
	if (textfield->need_redraw && textfield->text != NULL)
		trigger_gui_custom_event(textfield->on_text_change, textfield->text);
	return (true);
}

bool		update_textfield_func(void *param)
{
	t_gui_textfield	*textfield;
	t_vec2i			pos;
	t_vec2i			mouse_pos;

	textfield = param;
	mouse_pos = get_mouse_position();
	pos = get_component_pos((t_component *)textfield);
	if (get_button_down(SDL_BUTTON_LEFT, NULL)
		|| get_button_down(SDL_BUTTON_RIGHT, NULL))
	{
		if (is_in_box(mouse_pos,
			&(SDL_Rect){pos.x, pos.y, textfield->component.rect.w,
			textfield->component.rect.h}))
			textfield->is_focus = true;
		else if (textfield->is_focus)
		{
			textfield->component.need_redraw = true;
			textfield->is_focus = false;
		}
	}
	if (textfield->is_focus)
		return (update_textfield_func_p2(textfield));
	return (true);
}
