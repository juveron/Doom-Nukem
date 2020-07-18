/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   context.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/17 12:09:55 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 11:11:29 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "context.h"
#include "libft.h"
#include <stdio.h>
#include <SDL2/SDL_ttf.h>
#include "free_all.h"

int					init_context(void)
{
	t_context	*c;

	if (!(c = get_context()))
		return (0);
	if (SDL_Init(SDL_INIT_VIDEO) != 0)
		return (sdl_throw_error("ERROR: SDL init fail!", 0, false));
	if (TTF_Init() == -1)
		return (sdl_throw_error("ERROR: TTF init fail!", 0, false));
	if (!(c->font = TTF_OpenFont("./assets/DejaVuSansMono.ttf", 16)))
		return (sdl_throw_error("ERROR: Fail to load font!", 0, false));
	ft_printf("SDL initialised!...\n");
	if (!(c->window = map_init(sizeof(t_window *))))
		return (sdl_throw_error("ERROR: malloc fail!", 0, false));
	if (!vector_init(&c->gui_trigger, sizeof(t_event_vector)))
		return (sdl_throw_error("ERROR: Failed to init gui event", 0, false));
	clock_restart(&c->timer);
	c->run = true;
	SDL_StartTextInput();
	return (1);
}

inline t_context	*get_context(void)
{
	static	t_context	*context;

	if (!context)
	{
		context = (t_context *)ft_memalloc(sizeof(t_context));
	}
	return (context);
}

void				free_context(void)
{
	t_context	*context;

	context = get_context();
	if (context)
	{
		free_window();
		TTF_CloseFont(context->font);
		vector_free(&context->gui_trigger);
		ft_memdel((void **)&context->handle_event.drop.file_name);
		free(context);
	}
	SDL_StopTextInput();
	TTF_Quit();
	SDL_Quit();
}

bool				is_running(void)
{
	return (get_context()->run);
}
