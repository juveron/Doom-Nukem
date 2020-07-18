/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels_selection.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/24 10:18:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 11:10:20 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"
#include "levels_selection_internal.h"

static SDL_Color				get_color(size_t i,
	t_gui_levels_selection *levels_selection)
{
	SDL_Color	color;

	if (i + levels_selection->start == levels_selection->selected_index)
		color = (SDL_Color){255, 0, 0, 0};
	else if (*levels_selection->current_map_index == i
		+ levels_selection->start)
		color = (SDL_Color){0, 0, 255, 0};
	else
		color = (SDL_Color){255, 255, 255, 0};
	return (color);
}

static bool						draw_text(
	t_gui_levels_selection *levels_selection, size_t i, t_doom_map **maps)
{
	SDL_Surface	*surface;

	if (!(surface = TTF_RenderText_Blended(levels_selection->font,
		maps[i + levels_selection->start]->name, get_color(i,
		levels_selection))))
		return (false);
	SDL_BlitSurface(surface, NULL,
		levels_selection->component.surface, &(SDL_Rect){10, 5 + 30 * i,
		0, 0});
	SDL_FreeSurface(surface);
	return (true);
}

bool							draw_levels_selection_func(void *param)
{
	t_gui_levels_selection	*levels_selection;
	size_t					i;
	t_doom_map				**maps;

	i = 0;
	levels_selection = param;
	maps = levels_selection->levels->items;
	while (i < levels_selection->size)
	{
		if (i + levels_selection->start >= levels_selection->levels->total)
			break ;
		if (maps[i + levels_selection->start]->name[0] != '\0')
			if (!draw_text(levels_selection, i, maps))
				return (false);
		draw_line((t_vec2i){0, (i + 1) * 30},
			(t_vec2i){levels_selection->component.rect.w, (i + 1) * 30},
			0xFF, levels_selection->component.surface);
		i++;
	}
	return (true);
}

static t_gui_levels_selection	*return_error(
	t_gui_levels_selection *levels_selection)
{
	free(levels_selection);
	return (NULL);
}

t_gui_levels_selection			*create_levels_selection(SDL_Rect rect,
	t_vector *levels, t_env *env)
{
	t_gui_levels_selection	*levels_selection;

	if (!(levels_selection = ft_memalloc(sizeof(t_gui_levels_selection))))
		return (NULL);
	if (init_component(&levels_selection->component, &rect, true,
		0x777777FF) == false)
		return (return_error(levels_selection));
	levels_selection->levels = levels;
	levels_selection->current_map_index = &env->current_map_index;
	levels_selection->component.elem_type = GUI_ELEM_CUSTOM;
	levels_selection->component.draw = &draw_levels_selection_func;
	levels_selection->component.update = &update_levels_selection_func;
	levels_selection->size = rect.h / 30;
	levels_selection->start = 0;
	levels_selection->font = env->fonts.deja_vu_sans_momo_16;
	levels_selection->end = levels_selection->size - 1;
	levels_selection->on_selection_change = create_event_handler(
		CUSTOM_EVENT_TYPE);
	return (levels_selection);
}
