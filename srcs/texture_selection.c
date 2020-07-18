/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selection.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:35:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 11:15:39 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_selection_internal.h"

char					*get_right_name(char *path)
{
	size_t	len;

	len = ft_strlen(path);
	while (len)
	{
		if (path[len - 1] == '/')
			return (path + len);
		len--;
	}
	return (path);
}

t_gui_texture_selection	*create_texture_selection(SDL_Rect rect, t_env *env)
{
	t_gui_texture_selection	*texture_selection;

	if (!(texture_selection = ft_memalloc(sizeof(t_gui_texture_selection))))
		return (NULL);
	init_component(&texture_selection->component, &rect, true, 0x777777FF);
	texture_selection->component.elem_type = GUI_ELEM_CUSTOM;
	texture_selection->component.draw = &draw_texture_selection_func;
	texture_selection->component.update = &update_texture_selection_func;
	texture_selection->env = env;
	texture_selection->on_selection_change = create_event_handler(
		CUSTOM_EVENT_TYPE);
	return (texture_selection);
}

bool					destroy_texture_selection(
	t_gui_texture_selection **selec)
{
	int	ret;

	ret = 0;
	if (*selec == NULL)
		return (true);
	ret += !component_remove_from_parent(*selec);
	destroy_component(&(*selec)->component);
	destroy_event_handler((*selec)->on_selection_change);
	free(*selec);
	*selec = NULL;
	return (ret == 0);
}
