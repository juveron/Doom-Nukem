/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_grid.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:44:39 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 12:44:58 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

void	set_grid_info(t_env *env)
{
	env->editor.subdiv = env->editor.zoom / env->editor.div;
	env->editor.begin.x = (env->editor.offset.x - floorf(env->editor.offset.x))
		* env->editor.zoom - env->editor.zoom;
	env->editor.begin.y = (env->editor.offset.y - floorf(env->editor.offset.y))
		* env->editor.zoom - env->editor.zoom;
	env->editor.offset_z.x = env->editor.offset.x * env->editor.zoom;
	env->editor.offset_z.y = env->editor.offset.y * env->editor.zoom;
}

void	draw_grid(t_env *env)
{
	t_editor	*editor;
	size_t		i;

	i = 0;
	editor = &env->editor;
	while ((editor->begin.x + editor->subdiv * i) < WIDTH)
	{
		draw_line_clip((t_clipping_line){vec2i(editor->begin.x + editor->subdiv
			* i, 0), vec2i(editor->begin.x + editor->subdiv * i, HEIGHT - 1),
			vec2i(0, 0), vec2i(WIDTH, HEIGHT)}, 0x8a8a8a,
			env->main_window->surface);
		i++;
	}
	i = 0;
	while ((editor->begin.y + editor->subdiv * i) < HEIGHT)
	{
		draw_line_clip((t_clipping_line){vec2i(0, editor->begin.y
			+ editor->subdiv * i), vec2i(WIDTH - 1, editor->begin.y
			+ editor->subdiv * i), vec2i(0, 0), vec2i(WIDTH, HEIGHT)},
			0x8a8a8a, env->main_window->surface);
		i++;
	}
}
