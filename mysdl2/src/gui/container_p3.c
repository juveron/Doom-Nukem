/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container_p3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/29 19:20:36 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 23:01:41 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool	init_container(t_container *container, SDL_Rect *rect,
	bool use_background, t_color color)
{
	container->component.elem_type = GUI_ELEM_CONTAINER;
	if (!vector_init(&container->array_component, sizeof(t_component *)))
		return (false);
	if (!init_component(&container->component, rect, use_background, color))
	{
		vector_free(&container->array_component);
		return (false);
	}
	return (true);
}

bool	container_clear(t_container *container)
{
	while (container->array_component.total)
		container_delete_index(container, 0);
	return (true);
}
