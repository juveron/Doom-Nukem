/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render_object.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/02 11:37:43 by kguibout          #+#    #+#             */
/*   Updated: 2020/04/29 13:05:30 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

t_render_object	*create_render_object(char *name, t_mesh *mesh,
	bool has_custom_material, t_material *custom_material)
{
	t_render_object	*render_object;

	if (!(render_object = ft_memalloc(sizeof(t_render_object))))
		return (NULL);
	if (!(render_object->name = ft_strdup(name)))
	{
		free(render_object);
		return (NULL);
	}
	render_object->mesh = mesh;
	render_object->has_custom_material = has_custom_material;
	if (has_custom_material)
		render_object->custom_material = custom_material;
	return (render_object);
}

void			destroy_render_object(t_render_object **render_object)
{
	if (*render_object == NULL)
		return ;
	free((*render_object)->name);
	free(*render_object);
	*render_object = NULL;
}
