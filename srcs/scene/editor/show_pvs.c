/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   show_pvs.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 03:05:21 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/10 03:10:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "editor.h"
#include "render.h"

bool	show_pvs(t_sector *sector, t_env *env)
{
	size_t		i;
	t_unique_id	*id;
	t_vector	vector;

	if (!compute_pvs(sector, &vector))
		return (false);
	draw_sector_highlight(sector, env, 0x00FF00);
	i = 0;
	id = vector.items;
	while (i < vector.total)
	{
		draw_sector_highlight(*(t_sector **)map_get(env->current_map->sectors,
			id[i]), env, 0x00FF00);
		++i;
	}
	vector_free(&vector);
	return (true);
}
