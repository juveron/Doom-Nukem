/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/02 18:31:56 by thboura           #+#    #+#             */
/*   Updated: 2020/06/08 14:48:20 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "history_internal.h"

void		reset_history_window_pos(t_env *env, t_window *history_window)
{
	t_vec2i	main_pos;
	t_vec2i	history_pos;

	SDL_GetWindowPosition(env->main_window->handle, &main_pos.x, &main_pos.y);
	history_pos = vec2i(main_pos.x + env->main_window->size.x, main_pos.y);
	SDL_SetWindowPosition(history_window->handle, history_pos.x, history_pos.y);
}

static void	destroy_event_selection(t_gui_event_selection **event_selec)
{
	if (*event_selec == NULL)
		return ;
	destroy_component(&(*event_selec)->component);
	free(*event_selec);
	*event_selec = NULL;
}

bool		destroy_history(t_history_window *history)
{
	if (history->available)
	{
		history->available = false;
		destroy_event_selection(&history->event_selection);
		if (!destroy_window(history->window))
			return (false);
	}
	return (true);
}

bool		init_history(t_env *env, t_history_window *history)
{
	t_vec2i		dimension;
	t_vec2i		position;

	if (history->available)
		return (true);
	position = vec2i(env->main_window->pos.x + env->main_window->size.x,
		env->main_window->pos.y);
	dimension = vec2i(200, env->main_window->size.y);
	if (!(history->window = create_window("History", position, dimension, 0)))
		return (false);
	if (!(history->event_selection = create_event_selection(env,
		(SDL_Rect){0, 0, dimension.x, dimension.y},
		&env->editor.event_handler)))
		return (false);
	container_add(history->window->main_container, history->event_selection);
	history->available = true;
	SDL_RaiseWindow(env->main_window->handle);
	return (true);
}
