/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_debug.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/28 09:47:30 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 14:55:42 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		print_grid_debug(t_env *env)
{
	static t_vec2f	last_offset = (t_vec2f){0, 0};
	static float	last_zoom = 0;

	if (last_offset.x != env->editor.offset.x
		|| last_offset.y != env->editor.offset.y
		|| last_zoom != env->editor.zoom)
	{
		ft_printf("offset.x = %f, offset.y = %f, zoom = %f\n",
			env->editor.offset.x, env->editor.offset.y, env->editor.zoom);
		ft_printf("env->subdiv = %f, env->begin.x = %f, env->begin.y = %f\n",
			env->editor.subdiv, env->editor.begin.x, env->editor.begin.y);
		last_offset = env->editor.offset;
		last_zoom = env->editor.zoom;
	}
}

void		print_snap_point_debug(t_env *env)
{
	static t_vertex	last_pos;

	if (last_pos.v.x != env->editor.position_map.v.x
		|| last_pos.v.y != env->editor.position_map.v.y)
	{
		ft_printf("%f %f\n", env->editor.position_map.v.x,
			env->editor.position_map.v.y);
		last_pos = env->editor.position_map;
	}
}

void		print_global_state_debug(t_env *env)
{
	if (!env->selection_state)
		return ;
	blit_surface(env->selection_state,
		rect(WIDTH - env->selection_state->w - 20, 20, 0, 0), env->main_window);
}

static void	print_point_selected_debug_p2(int *line_number,
	SDL_Surface *surface, t_env *env)
{
	(*line_number)--;
	ft_snprintf(env->buff, sizeof(env->buff), "Position: x %f z %f",
		env->editor.drag_point.dragged_point->v.v.x, env->editor.drag_point.
		dragged_point->v.v.z);
	surface = TTF_RenderText_Blended(env->fonts.deja_vu_sans_momo_16,
		env->buff, (SDL_Color){255, 255, 255, 0});
	blit_surface(surface, rect(WIDTH - surface->w - 10,
		HEIGHT - (30 * *line_number), 0, 0), env->main_window);
	SDL_FreeSurface(surface);
}

void		print_point_selected_debug(t_env *env)
{
	SDL_Surface	*surface;
	int			line_number;

	if (!env->editor.drag_point.point_is_dragged)
		return ;
	line_number = 3;
	ft_snprintf(env->buff, sizeof(env->buff), "Point ID: %lu",
		env->editor.drag_point.dragged_point->id);
	surface = TTF_RenderText_Blended(env->fonts.deja_vu_sans_momo_16,
		env->buff, (SDL_Color){255, 255, 255, 0});
	blit_surface(surface, rect(WIDTH - surface->w - 10,
		HEIGHT - (30 * line_number), 0, 0), env->main_window);
	SDL_FreeSurface(surface);
	line_number--;
	ft_snprintf(env->buff, sizeof(env->buff), "Number of sectors: %lu",
		env->editor.drag_point.dragged_point->sector->total);
	surface = TTF_RenderText_Blended(env->fonts.deja_vu_sans_momo_16,
		env->buff, (SDL_Color){255, 255, 255, 0});
	blit_surface(surface, rect(WIDTH - surface->w - 10,
		HEIGHT - (30 * line_number), 0, 0), env->main_window);
	SDL_FreeSurface(surface);
	print_point_selected_debug_p2(&line_number, surface, env);
}
