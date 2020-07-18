/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   label.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/11 05:31:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/11 19:03:19 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool		draw_label_func(void *param)
{
	t_gui_label	*label;

	label = param;
	if (label->need_redraw)
	{
		SDL_FreeSurface(label->surface);
		if (!(label->surface = text_surface(label->name, label->color,
			label->font)))
			return (false);
		label->need_redraw = false;
		SDL_FreeSurface(label->component.surface);
		if (!(label->component.surface = SDL_CreateRGBSurfaceWithFormat(0,
			label->surface->w, label->surface->h, 32,
			SDL_PIXELFORMAT_RGBA8888)))
			return (false);
		if (label->component.use_background)
			draw_rectangle((SDL_Rect){0, 0, label->component.rect.w,
				label->component.rect.h}, label->component.background,
				label->component.surface);
		label->component.rect.w = label->surface->w;
		label->component.rect.h = label->surface->h;
	}
	SDL_BlitSurface(label->surface, NULL,
		label->component.surface, &(SDL_Rect){0, 0, 0, 0});
	return (true);
}

bool		update_label_func(void *param)
{
	(void)param;
	return (true);
}

static void	create_label_p2(t_gui_label *label)
{
	label->component.elem_type = GUI_ELEM_LABEL;
	label->component.draw = &draw_label_func;
	label->component.update = &update_label_func;
	label->need_redraw = true;
}

t_gui_label	*create_label(const t_vec2i pos, const t_color color,
	TTF_Font *font, const t_color background_color)
{
	t_gui_label	*label;
	t_vec2i		size;

	if (!(label = ft_memalloc(sizeof(t_gui_label)))
		|| !(label->name = ft_strdup("label")))
	{
		destroy_label(&label);
		return (NULL);
	}
	TTF_SizeText(font, label->name, &size.x, &size.y);
	if (!init_component(&label->component, &(SDL_Rect){pos.x, pos.y, size.x,
		size.y}, false, 0))
	{
		destroy_label(&label);
		return (NULL);
	}
	if (background_color & 255)
	{
		label->component.use_background = true;
		label->component.background = background_color;
	}
	create_label_p2(label);
	label->font = font;
	label->color = color;
	return (label);
}

bool		destroy_label(t_gui_label **label)
{
	int	ret;

	ret = 0;
	if (*label == NULL)
		return (true);
	ret += !component_remove_from_parent(*label);
	destroy_component(&(*label)->component);
	free((*label)->name);
	SDL_FreeSurface((*label)->surface);
	free(*label);
	*label = NULL;
	return (ret == 0);
}
