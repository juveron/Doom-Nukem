/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_p3.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 13:08:00 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 19:57:16 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_dlist		*get_dlist_by_index(t_dlist_handler *list, size_t index)
{
	size_t		i;
	t_dlist		*tmp_dlist;

	if (index >= list->size || list->head == NULL)
		return (NULL);
	tmp_dlist = list->head;
	i = 0;
	while (i < index)
	{
		if (tmp_dlist == list->tail)
			return (NULL);
		tmp_dlist = tmp_dlist->next;
		i++;
	}
	return (tmp_dlist);
}

size_t		get_dlist_index(t_dlist_handler *list, t_dlist *dlist)
{
	size_t		i;
	t_dlist		*tmp_dlist;

	if (dlist == NULL || list->head == NULL)
		return ((size_t)-1);
	tmp_dlist = list->head;
	i = 0;
	while (tmp_dlist != NULL)
	{
		if (tmp_dlist == dlist)
			return (i);
		tmp_dlist = tmp_dlist->next;
		i++;
	}
	return ((size_t)-1);
}

bool		set_selected_event(t_gui_event_selection *selection,
	t_dlist *tmp_dlist, size_t index)
{
	size_t		i;

	i = get_dlist_index(selection->event_handler->event_list,
		selection->event_handler->current_event);
	if (i == (size_t)-1)
		return (true);
	while (selection->event_handler->current_event != tmp_dlist)
	{
		if (i > index)
		{
			if (!undo_event(selection->event_handler, selection->env))
				return (false);
			i--;
		}
		else if (i < index)
		{
			if (!redo_event(selection->event_handler, selection->env))
				return (false);
			i++;
		}
	}
	return (true);
}

static bool	draw_event_selection_func_p2(t_gui_event_selection *event_selection,
	t_dlist **event, SDL_Color color, size_t i)
{
	t_recorded_event		*tmp_cast;
	SDL_Surface				*surface;

	tmp_cast = (t_recorded_event *)(*event)->content;
	if (!(surface = TTF_RenderText_Blended(event_selection->font,
		get_event_type(tmp_cast->type), color)))
		return (false);
	SDL_BlitSurface(surface, NULL, event_selection->component.surface,
		&(SDL_Rect){10, 5 + 30 * i, 0, 0});
	SDL_FreeSurface(surface);
	draw_line((t_vec2i){0, (i + 1) * 30}, (t_vec2i){event_selection->
		component.rect.w, (i + 1) * 30}, 0xFF,
		event_selection->component.surface);
	*event = (*event)->next;
	return (true);
}

bool		draw_event_selection_func(void *param)
{
	t_gui_event_selection	*event_selection;
	t_dlist					*event;
	SDL_Color				color;
	size_t					i;

	event_selection = param;
	i = 0;
	event = get_dlist_by_index(event_selection->event_handler->event_list,
		event_selection->start);
	while (i < event_selection->size)
	{
		if (i + event_selection->start >= event_selection->event_handler->
			event_list->size)
			break ;
		if (i + event_selection->start == event_selection->selected_index - 1)
			color = (SDL_Color){255, 0, 0, 0};
		else if (event_selection->selected_index != 0 && i + event_selection->
			start < event_selection->selected_index - 1)
			color = (SDL_Color){255, 255, 255, 0};
		else
			color = (SDL_Color){192, 192, 192, 0};
		if (!draw_event_selection_func_p2(event_selection, &event, color, i++))
			return (false);
	}
	return (true);
}
