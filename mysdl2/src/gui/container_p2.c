/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/19 12:47:56 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/12 03:05:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

bool		container_delete(t_container *container, t_component *component)
{
	size_t	i;
	size_t	size;

	size = vector_total(&container->array_component);
	i = 0;
	while (i < size)
	{
		if (*(t_component **)vector_get(&container->array_component,
			i) == component)
			return (container_delete_index(container, i));
		++i;
	}
	return (true);
}

t_vec2i		get_component_pos(t_component *component)
{
	t_vec2i	pos;

	pos = (t_vec2i){0, 0};
	while (component)
	{
		pos.x += component->rect.x;
		pos.y += component->rect.y;
		component = component->parent;
	}
	return (pos);
}

t_container	*get_right_container(t_component *component)
{
	if (component->elem_type == GUI_ELEM_CUSTOM_WINDOW)
		return (((t_gui_custom_window *)component)->container);
	else
		return (NULL);
}

bool		destroy_container(t_container **container)
{
	int	ret;

	ret = 0;
	if (*container == NULL)
		return (true);
	ret += !component_remove_from_parent(*container);
	destroy_component(&(*container)->component);
	vector_free(&(*container)->array_component);
	free(*container);
	*container = NULL;
	return (ret == 0);
}

t_container	*create_container(SDL_Rect rect, bool use_background,
	t_color color)
{
	t_container	*container;

	if (!(container = ft_memalloc(sizeof(t_container))))
		return (NULL);
	container->component.elem_type = GUI_ELEM_CONTAINER;
	if (!vector_init(&container->array_component, sizeof(t_container *)))
	{
		free(container);
		return (NULL);
	}
	init_component(&container->component, &rect, use_background, color);
	return (container);
}
