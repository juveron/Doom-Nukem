/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sector_highlight.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/09 22:18:18 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/12 12:09:37 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"

static void	draw_wall(t_wall *wall, t_env *env, t_color color)
{
	draw_line_clip((t_clipping_line){grid_to_win(&wall->v1->v.v, env),
		grid_to_win(&wall->v2->v.v, env), vec2i(0, 0), vec2i(WIDTH, HEIGHT)},
		color, env->main_window->surface);
}

void		draw_sector_highlight(t_sector *sector, t_env *env, t_color color)
{
	size_t	i;
	t_wall	*walls;

	i = 0;
	walls = sector->walls.items;
	while (i < sector->walls.total)
	{
		draw_wall(&walls[i], env, color);
		++i;
	}
}
