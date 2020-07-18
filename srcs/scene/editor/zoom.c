/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   zoom.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:37:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 14:37:32 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	zoom(t_vec2i pos, t_env *env, float z)
{
	t_vec2f	size;
	float	px;
	float	py;

	if (env->editor.zoom * z <= 5 || env->editor.zoom * z >= 400)
		return ;
	px = pos.x / (float)WIDTH;
	py = pos.y / (float)HEIGHT;
	size.x = WIDTH / (env->editor.zoom) - WIDTH / (env->editor.zoom * z);
	size.y = HEIGHT / (env->editor.zoom) - HEIGHT / (env->editor.zoom * z);
	env->editor.zoom *= z;
	env->editor.offset.x -= px * size.x;
	env->editor.offset.y -= py * size.y;
	env->need_redraw = true;
}
