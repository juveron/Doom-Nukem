/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   notify.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 08:13:48 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/07 13:33:18 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		destroy_notify(t_env *env)
{
	free(env->editor.notify.msg);
	SDL_FreeSurface(env->editor.notify.surface);
}

void		send_notify(char *msg, t_color color, t_env *env)
{
	t_notify	*notify;

	notify = &env->editor.notify;
	notify->color = color;
	ft_strdel(&notify->msg);
	notify->msg = ft_strdup(msg);
	notify->print_msg = true;
	notify->surface_init = false;
	clock_restart(&notify->clock);
	env->need_redraw = true;
}

static void	clock_notify(t_env *env, t_notify *notify)
{
	if (clock_get_milliseconds(&notify->clock) < 2000.f && notify->surface
		&& env->need_redraw == true)
		blit_surface(notify->surface, rect(10, HEIGHT - notify->surface->h
			- 10, 0, 0), env->main_window);
}

void		update_notify(t_env *env, t_notify *notify)
{
	if (notify->print_msg && clock_get_milliseconds(&notify->clock) >= 2000.f)
	{
		notify->print_msg = false;
		SDL_FreeSurface(notify->surface);
		notify->surface = NULL;
		free(notify->msg);
		notify->msg = NULL;
		env->need_redraw = true;
	}
}

bool		draw_notify(t_env *env)
{
	t_notify	*notify;

	notify = &env->editor.notify;
	if (notify->print_msg == true)
	{
		if (notify->surface_init == false)
		{
			SDL_FreeSurface(notify->surface);
			if (!(notify->surface = TTF_RenderText_Blended(env->
				fonts.deja_vu_sans_momo_16, notify->msg,
				(SDL_Color){(notify->color >> 16) % 256, (notify->color >> 8)
				% 256, (notify->color) % 256, 0})))
				return (false);
			env->need_redraw = true;
			notify->surface_init = true;
		}
		clock_notify(env, notify);
	}
	return (true);
}
