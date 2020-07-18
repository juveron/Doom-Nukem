/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_gui.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 13:44:33 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/11 19:04:33 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool	update_component(t_component *component)
{
	if (component->elem_type == GUI_ELEM_CONTAINER)
	{
		if (!update_container((t_container *)component))
			return (false);
	}
	else
	{
		if (!component->update(component))
			return (false);
	}
	if (component->elem_type == GUI_ELEM_CUSTOM_WINDOW)
	{
		if (!update_container(((t_gui_custom_window *)component)->container))
			return (false);
	}
	return (true);
}

bool	update_container(t_container *container)
{
	t_component	*component;
	size_t		i;

	i = 0;
	while (i < container->array_component.total)
	{
		component = *(t_component **)vector_get(&container->array_component, i);
		if (component->is_visible)
			if (!update_component(component))
				return (false);
		i++;
	}
	return (true);
}

void	*copy_surface(void *dest, const void *src, const size_t n)
{
	t_u32	*tmp1;
	t_u32	*tmp2;
	size_t	i;

	i = 0;
	tmp1 = (t_u32 *)dest;
	tmp2 = (t_u32 *)src;
	while (n > i)
	{
		if (tmp2[i] & 0xFF)
			tmp1[i] = tmp2[i] >> 8;
		i++;
	}
	return (dest);
}

bool	update_gui(t_window *window)
{
	size_t		i;
	t_component	**component;
	SDL_Rect	rect;

	if (!update_container(window->main_container)
		|| !trigger_gui_event() || !draw_container(window->main_container))
		return (false);
	window->need_redraw = window->main_container->component.need_redraw;
	window->main_container->component.need_redraw = false;
	if (!window->main_container->component.need_redraw && !window->force_redraw)
		return (true);
	component = window->main_container->array_component.items;
	i = 0;
	while (i < window->main_container->array_component.total)
	{
		if (component[i]->is_visible)
		{
			rect = component[i]->rect;
			if (SDL_BlitSurface(component[i]->surface, NULL,
				window->surface, &rect) == -1)
				return (false);
		}
		i++;
	}
	return (true);
}
