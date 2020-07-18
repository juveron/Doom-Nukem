/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_selection_p3.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/03 09:35:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 11:44:37 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "texture_selection_internal.h"

static t_u32	get_texture(SDL_Surface *texture, t_vec2f *uv)
{
	int	x;
	int	y;

	x = (uv->x - floorf(uv->x)) * (texture->w - 1);
	y = (1 - (uv->y - floorf(uv->y))) * (texture->h - 1);
	return (((t_u32 *)texture->pixels)[y * texture->w + x]);
}

static void		draw_preview_p2(t_tex_sel *s)
{
	int	x;

	x = 0;
	while (x < s->rect.w)
	{
		s->uv = vec2f_add(s->uv, s->step);
		if (x + s->rect.x >= s->win->w || x + s->rect.x < 0
			|| s->y + s->rect.y >= s->win->h || s->y + s->rect.y < 0)
		{
			x++;
			continue ;
		}
		((t_u32 *)s->win->pixels)[(x + s->rect.x) + (s->y + s->rect.y)
			* s->win->w] = (get_texture(s->surface, &s->uv) << 8) | 0xFF;
		x++;
	}
}

static void		draw_preview(SDL_Rect rect, SDL_Surface *win,
	SDL_Surface *surface)
{
	t_vec2f		uv2;
	t_tex_sel	s;

	s.win = win;
	s.surface = surface;
	s.step = vec2f(1 / (float)rect.w, 0);
	s.uv = vec2f(0, 0);
	s.y = 0;
	s.rect = rect;
	while (s.y < s.rect.h)
	{
		if (s.y + s.rect.y >= win->h)
			break ;
		uv2 = s.uv;
		draw_preview_p2(&s);
		s.uv.x = uv2.x - s.step.y;
		s.uv.y = uv2.y + s.step.x;
		s.y++;
	}
}

static void		draw_out_line_selection(
	t_gui_texture_selection *texture_selection, size_t i)
{
	if (texture_selection->section_pos >= 0
		&& i + texture_selection->start == (size_t)texture_selection->
			section_pos)
		draw_rectangle((SDL_Rect){4 + 95 * (i % 5), 4 + 95
			* (i / 5), 92, 92}, 0xFF0000FF,
			texture_selection->component.surface);
	else
		draw_rectangle((SDL_Rect){4 + 95 * (i % 5), 4 + 95
			* (i / 5), 92, 92}, 0xFFFFFFFF,
			texture_selection->component.surface);
}

bool			draw_texture_selection_func(void *param)
{
	t_gui_texture_selection	*texture_selection;
	size_t					i;
	t_texture				*texture;

	texture_selection = param;
	i = 0;
	while (i + texture_selection->start < texture_selection->env->
		texture_array->total + 1)
	{
		if (i > 24)
			break ;
		if (i + texture_selection->start != 0)
			texture = *(t_texture **)texture_selection->env->texture_array->
				elem[texture_selection->start + i - 1].data;
		draw_out_line_selection(texture_selection, i);
		if (i + texture_selection->start != 0)
			draw_preview((SDL_Rect){5 + 95 * (i % 5), 5 + 95
				* (i / 5), 90, 90}, texture_selection->component.surface,
				texture->surface);
		i++;
	}
	return (true);
}
