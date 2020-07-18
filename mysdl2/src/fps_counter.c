/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fps_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/26 15:19:08 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:10:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "window.h"
#include "draw.h"
#include "SDL2/SDL_ttf.h"
#include "text.h"

/*
** Enable framerate counter in the window.
**
** \param   win Window pointer to the window
**
** \return  1 or 0 if error occurs.
*/

int		enable_fps_counter(t_window *win)
{
	t_fps_counter	*fps;

	if (win->fps_counter)
		return (1);
	if (!(fps = ft_memalloc(sizeof(t_fps_counter))))
	{
		return (sdl_throw_error("ERROR: malloc fail on fps_counter!", 0,
			false));
	}
	if (!(fps->background = SDL_CreateRGBSurface(0, 110, 40, 32, 0, 0, 0, 0)))
		return (0);
	draw_rectangle(rect(0, 0, fps->background->w, fps->background->h),
		0x808080, fps->background);
	if (!(fps->text = text_surface("FPS: null", 0x0, get_context()->font)))
		return (0);
	clock_restart(&fps->timer);
	win->fps_counter = fps;
	return (1);
}

/*
** Disable framerate counter in the window.
**
** \param   win Window pointer to the window
*/

void	disable_fps_counter(t_window *win)
{
	SDL_FreeSurface(win->fps_counter->background);
	SDL_FreeSurface(win->fps_counter->text);
	ft_memdel((void **)&win->fps_counter);
}

bool	update_fps_counter(t_window *win)
{
	t_fps_counter	*fps;
	char			text[32];

	fps = win->fps_counter;
	if (!fps)
		return (true);
	fps->frames++;
	if (clock_get_seconds(&fps->timer) >= 1.f)
	{
		SDL_FreeSurface(fps->text);
		ft_snprintf(text, sizeof(text), "FPS: %d", fps->frames);
		if (!(fps->text = text_surface(text, 0x0, get_context()->font)))
			return (false);
		fps->frames = 0;
		clock_restart(&fps->timer);
	}
	if (SDL_BlitSurface(fps->background, NULL, win->surface,
			&(SDL_Rect){.x = 0, .y = 0})
		|| SDL_BlitSurface(fps->text, NULL, win->surface, &(SDL_Rect){.x = 10,
			.y = 10}))
		return (false);
	return (true);
}
