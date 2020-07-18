/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   select.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 11:30:22 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 22:25:32 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		free_selection_mode(t_env *env)
{
	SDL_FreeSurface(env->selection_state);
}

static void	change_selection_mode_p2(t_env *env, t_editor_selection_state state)
{
	if (state == EDITOR_SELECT_POINT)
		env->selection_state = TTF_RenderText_Blended(env->fonts.
			deja_vu_sans_momo_16, "Point mode",
			(SDL_Color){255, 255, 255, 0});
	else if (state == EDITOR_SELECT_LINE)
		env->selection_state = TTF_RenderText_Blended(env->fonts.
			deja_vu_sans_momo_16, "Line mode",
			(SDL_Color){255, 255, 255, 0});
	else if (state == EDITOR_LEVELS)
		env->selection_state = TTF_RenderText_Blended(env->fonts.
			deja_vu_sans_momo_16, "Level mode",
			(SDL_Color){255, 255, 255, 0});
	else if (state == EDITOR_OBJECT)
		env->selection_state = TTF_RenderText_Blended(env->fonts.
			deja_vu_sans_momo_16, "Object mode",
			(SDL_Color){255, 255, 255, 0});
	else
		env->selection_state = TTF_RenderText_Blended(env->fonts.
			deja_vu_sans_momo_16, "Unknown mode (WTF ?!)",
			(SDL_Color){255, 255, 255, 0});
}

bool		change_selection_mode(t_env *env, t_editor_selection_state state)
{
	if (env->editor.state.section_state != state
		&& DEBUG_SELECTION_STATE)
	{
		SDL_FreeSurface(env->selection_state);
		change_selection_mode_p2(env, state);
		if (!env->selection_state)
			return (false);
		env->editor.state.section_state = state;
		env->need_redraw = true;
	}
	return (true);
}
