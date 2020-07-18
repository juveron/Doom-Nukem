/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_multi_point.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 12:43:27 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 12:43:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	check_multiple_points(t_env *env)
{
	t_point	*v;
	t_u32	i;
	bool	found;

	found = false;
	i = 0;
	while (i < env->current_map->vertices->total)
	{
		v = *(t_point **)map_get_index(env->current_map->vertices, i);
		if (v->v.v.x == env->editor.position_map.v.x
			&& v->v.v.z == env->editor.position_map.v.z)
		{
			if (!found)
				found = true;
			else
				return (true);
		}
		i++;
	}
	return (false);
}
