/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   component.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 23:32:02 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 22:56:16 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool	init_component(t_component *component, const SDL_Rect *rect,
	const bool use_background, const t_color color_background)
{
	component->rect = *rect;
	if (!(component->surface = SDL_CreateRGBSurfaceWithFormat(0, rect->w,
		rect->h, 32, SDL_PIXELFORMAT_RGBA8888)))
		return (false);
	component->is_visible = true;
	component->use_background = use_background;
	component->need_redraw = true;
	if (use_background)
		component->background = color_background;
	return (true);
}

void	destroy_component(t_component *component)
{
	SDL_FreeSurface(component->surface);
}

void	set_visible(t_component *component, const bool enable)
{
	if (component->is_visible != enable)
	{
		component->is_visible = enable;
		if (component->parent)
			component->parent->need_redraw = true;
	}
}

bool	component_remove_from_parent(void *component)
{
	t_component	*component1;

	component1 = component;
	if (component1->parent &&
		(component1->parent->elem_type == GUI_ELEM_CONTAINER
		|| component1->parent->elem_type == GUI_ELEM_MAIN_CONTAINER))
	{
		return (container_delete((t_container *)component1->parent,
				component1));
	}
	return (true);
}

void	component_change_background_color(void *component, bool use_background,
		t_color color)
{
	t_component	*p_component;

	p_component = component;
	if (p_component->use_background != use_background)
	{
		p_component->use_background = use_background;
		p_component->need_redraw = true;
	}
	if (use_background == 1 && p_component->background != color)
	{
		p_component->background = color;
		p_component->need_redraw = true;
	}
}
