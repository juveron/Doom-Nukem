/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_gui.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/30 23:34:05 by thboura           #+#    #+#             */
/*   Updated: 2020/07/11 19:02:30 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

static bool	draw_background(t_component *component)
{
	if (component->background_image)
	{
		if (SDL_BlitSurface(component->background_image, NULL,
			component->surface, &(SDL_Rect){0, 0, 0, 0}) == -1)
			return (false);
	}
	else
		draw_rectangle((SDL_Rect){0, 0, component->rect.w,
				component->rect.h}, component->background, component->surface);
	return (true);
}

static bool	draw_component_p2(t_component *component)
{
	SDL_Rect	rect;

	ft_memset(component->surface->pixels, 0,
		component->surface->h
		* component->surface->pitch);
	if (component->use_background)
		draw_background(component);
	if (!component->draw(component))
		return (false);
	component->parent->need_redraw = true;
	component->need_redraw = false;
	if (component->elem_type == GUI_ELEM_CUSTOM_WINDOW)
	{
		rect = ((t_gui_custom_window *)component)->container->component.
			rect;
		SDL_BlitSurface(((t_gui_custom_window *)component)->container->
			component.surface, NULL, component->surface, &rect);
	}
	return (true);
}

bool		draw_component(t_component *component)
{
	if (component->elem_type == GUI_ELEM_CONTAINER)
		if (!draw_container((t_container *)component))
			return (false);
	if (component->elem_type == GUI_ELEM_CUSTOM_WINDOW)
		if (!draw_container(((t_gui_custom_window *)component)->container))
			return (false);
	if (component->elem_type != GUI_ELEM_CONTAINER && component->need_redraw)
		return (draw_component_p2(component));
	return (true);
}

static bool	draw_container_p2(t_container *container, t_component **component,
	size_t i)
{
	SDL_Rect	rect;

	ft_memset(container->component.surface->pixels, 0,
		container->component.surface->h * container->component.surface->pitch);
	if (container->component.use_background
		&& !draw_background(&container->component))
		return (false);
	i = 0;
	while (i < container->array_component.total)
	{
		if (component[i]->is_visible)
		{
			rect = component[i]->rect;
			if (SDL_BlitSurface(component[i]->surface, NULL,
				container->component.surface, &rect))
				return (false);
		}
		i++;
	}
	if (container->component.parent)
		container->component.parent->need_redraw = true;
	if (container->component.elem_type != GUI_ELEM_MAIN_CONTAINER)
		container->component.need_redraw = false;
	return (true);
}

bool		draw_container(t_container *container)
{
	t_component	**component;
	size_t		i;

	component = container->array_component.items;
	i = 0;
	while (i < container->array_component.total)
	{
		if (component[i]->is_visible)
			if (!draw_component(component[i]))
				return (false);
		i++;
	}
	if (container->component.need_redraw
		&& !draw_container_p2(container, component, i))
		return (false);
	return (true);
}
