/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/01 22:53:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 16:25:50 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "window.h"

/*
** Set framerate for window.
**
** \param   framerate The new framerate.
*/

void	set_framerate(t_u32 framerate)
{
	get_context()->framerate_limit = framerate;
}

/*
** Destroy window.
**
** \param   win_id window id of th window
*/

bool	destroy_window(t_window *win)
{
	t_context	*context;
	int			ret;

	ret = 0;
	context = get_context();
	if (!win)
		return (true);
	if (win->fps_counter)
		disable_fps_counter(win);
	SDL_DestroyWindow(win->handle);
	ret += !map_delete(context->window, win->id);
	ret += !destroy_container(&win->main_container);
	free(win);
	return (ret == 0);
}

bool	is_over_window(t_window *win)
{
	return (win->is_over);
}

void	clear_window(t_window *win)
{
	ft_bzero(win->surface->pixels, win->surface->h
		* win->surface->pitch);
}
