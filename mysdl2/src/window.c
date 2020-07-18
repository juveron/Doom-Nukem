/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   window.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:49:47 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/11 19:05:59 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "window.h"

static bool		redraw_windows(void)
{
	size_t		i;
	size_t		length;
	t_context	*context;
	t_window	*current_window;

	context = get_context();
	length = map_total(context->window);
	i = 0;
	while (i < length)
	{
		current_window = *(t_window **)context->window->elem[i].data;
		if (current_window->force_redraw)
		{
			current_window->force_redraw = false;
			if (!update_fps_counter(current_window)
				|| SDL_UpdateWindowSurface(current_window->handle) == -1)
				return (false);
		}
		i++;
	}
	return (true);
}

/*
** Create framebuffer of the window.
**
** \param   win_id window id of the window
*/

bool			update_window(void)
{
	t_context	*context;
	int			remaining_time;

	context = get_context();
	if (context->framerate_limit > 0)
	{
		remaining_time = 1000 / (int)context->framerate_limit
			- (int)clock_get_milliseconds(&context->timer);
		if (remaining_time > 0)
			SDL_Delay(remaining_time);
		clock_restart(&context->timer);
	}
	if (!redraw_windows())
		return (false);
	if (context->context_3d)
	{
		context->context_3d->n_tri = 0;
		context->context_3d->n_tile_skiped = 0;
	}
	return (true);
}

static t_window	*init_window(t_window *window, t_vec2i *size)
{
	if (!(window->surface = SDL_GetWindowSurface(window->handle)))
	{
		SDL_DestroyWindow(window->handle);
		free(window);
		return ((t_window *)sdl_throw_error("ERROR: fail to get window \
			surface!", 0, 0));
	}
	window->id = SDL_GetWindowID(window->handle);
	window->size = *size;
	if (!init_main_container(window))
	{
		SDL_DestroyWindow(window->handle);
		free(window);
		return ((t_window *)sdl_throw_error("ERROR: fail to get window \
			surface!", 0, 0));
	}
	if (!map_add(get_context()->window, window->id, &window))
	{
		destroy_window(window);
		return ((t_window *)sdl_throw_error("ERROR: fail to get window \
			surface!", 0, 0));
	}
	return (window);
}

/*
** Create new window.
**
** \param   title  title of the window
** \param   pos  position f the window
** \param   size  size of the window
** \param   flags  flags of the window
**
** \return  Pointer of the new window, or NULL if error occurs
*/

t_window		*create_window(char *title, t_vec2i pos, t_vec2i size,
	t_u32 flags)
{
	t_window	*window;

	if (!(window = (t_window *)ft_memalloc(sizeof(t_window))))
	{
		return ((t_window *)sdl_throw_error("SDL_ERROR: Fail to create \
			window !", 0, 0));
	}
	if (flags & SDL_WINDOW_FULLSCREEN)
		pos = vec2i(0, 0);
	if (!(window->handle = SDL_CreateWindow(title, pos.x, pos.y,
					size.x, size.y, flags)))
	{
		free(window);
		return ((t_window *)sdl_throw_error("SDL_ERROR: Fail to create \
			window !", 0, 0));
	}
	SDL_GetWindowPosition(window->handle, &window->pos.x, &window->pos.y);
	ft_printf("Window created! (%s)\n", title);
	return (init_window(window, &size));
}

/*
** Create new window.
**
** \param   title  title of the window
** \param   pos  position f the window
** \param   size  size of the window
** \param   flags  flags of the window
**
** \return  Pointer of the new window, or NULL if error occurs
*/

t_window		*get_window_by_id(int win_id)
{
	t_window	**tmp;

	tmp = map_get(get_context()->window, win_id);
	if (tmp == NULL)
		return (NULL);
	else
		return (*tmp);
}
