/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   container.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/30 12:56:25 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 23:00:18 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gui.h"

t_component	*container_get_component(t_container *container, size_t index)
{
	t_component	**component;

	component = vector_get(&container->array_component, index);
	return (*component);
}

static bool	add_impl(t_container *container, t_component *component,
	int index)
{
	if (component->parent != NULL)
		container_delete(get_right_container(component->parent), component);
	if (index == -1)
	{
		if (!vector_push(&container->array_component, &component))
			return (false);
	}
	else
	{
		if (!vector_insert(&container->array_component, index, &component))
			return (false);
	}
	component->parent = &container->component;
	return (true);
}

bool		container_add(t_container *container, void *component)
{
	return (add_impl(container, (t_component *)component, -1));
}

bool		container_add_index(t_container *container, t_component *component,
	int index)
{
	return (add_impl(container, component, index));
}

bool		container_delete_index(t_container *container, size_t index)
{
	t_component	**comp;

	comp = vector_get(&container->array_component, index);
	(*comp)->parent = NULL;
	return (vector_delete(&container->array_component, index));
}
