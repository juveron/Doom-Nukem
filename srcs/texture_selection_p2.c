/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selection_p2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:35:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 11:49:01 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_selection_internal.h"

static bool			create_texture_internal(t_gui_texture_selection *selection,
	SDL_Surface *tex)
{
	t_texture	*texture;

	if (!(texture = create_texture(get_right_name(get_dropped_file()), tex,
		++selection->env->texture_unique_id)))
	{
		SDL_FreeSurface(tex);
		return (false);
	}
	selection->component.need_redraw = true;
	if (!map_add(selection->env->texture_array, texture->id, &texture))
	{
		destroy_texture(&texture);
		return (false);
	}
	return (true);
}

static int			load_droped_texture(t_vec2i *mouse_pos,
	t_gui_texture_selection *selection)
{
	SDL_Surface	*texture_surface;
	SDL_Surface	*tex;
	t_vec2i		pos;

	pos = get_component_pos((t_component *)selection);
	if (get_dropped_file() && is_in_box(*mouse_pos, &(SDL_Rect){pos.x, pos.y,
		selection->component.rect.w, selection->component.rect.h}))
	{
		if (!(texture_surface = import_tga(get_dropped_file(), false)))
		{
			send_notify("Fail to load texture !", 0xFF0000FF, selection->env);
			return (-1);
		}
		if (!(tex = SDL_ConvertSurfaceFormat(texture_surface,
			SDL_PIXELFORMAT_RGB888, 0)))
		{
			SDL_FreeSurface(texture_surface);
			ft_dprintf(2, "Fail to convert texture !\n");
			return (0);
		}
		SDL_FreeSurface(texture_surface);
		return (create_texture_internal(selection, tex));
	}
	return (1);
}

static bool			select_texture_p2(t_gui_texture_selection *selection)
{
	if (selection->section_pos == 0)
		selection->current_texture = NULL;
	else
		selection->current_texture = *(t_texture **)selection->
			env->texture_array->elem[selection->section_pos - 1].data;
	if (!trigger_gui_custom_event(selection->on_selection_change,
		selection))
		return (false);
	selection->component.need_redraw = true;
	return (true);
}

static bool			select_texture(t_vec2i *mouse_pos,
	t_gui_texture_selection *selection)
{
	int		tmp;
	t_vec2i	pos;

	pos = get_component_pos((t_component *)selection);
	if (selection->env->texture_array->total
		&& get_button_down(SDL_BUTTON_LEFT, NULL) && is_in_box(*mouse_pos,
		&((SDL_Rect){pos.x, pos.y, selection->component.rect.w,
		selection->component.rect.h})))
	{
		tmp = (mouse_pos->x - 5 - pos.x) / 95 + (mouse_pos->y - 5 - pos.y)
			/ 95 * 5;
		if (tmp >= 0 && tmp < (long)selection->env->texture_array->total + 1)
		{
			selection->section_pos = tmp + selection->start;
			return (select_texture_p2(selection));
		}
	}
	return (true);
}

bool				update_texture_selection_func(void *param)
{
	t_gui_texture_selection	*selection;
	t_vec2i					mouse_pos;
	t_vec2i					global_mouse_pos;
	t_vec2i					size;

	selection = param;
	global_mouse_pos = get_mouse_global_position();
	SDL_GetWindowPosition(selection->env->main_window->handle, &size.x,
		&size.y);
	mouse_pos.x = global_mouse_pos.x - size.x;
	mouse_pos.y = global_mouse_pos.y - size.y;
	scroll_texture(&mouse_pos, selection);
	if (!load_droped_texture(&mouse_pos, selection))
		return (false);
	return (select_texture(&mouse_pos, selection));
}
