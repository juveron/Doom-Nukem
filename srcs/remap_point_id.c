/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remap_point_id.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 13:44:47 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 21:47:18 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	remap_point_id(t_point *point, t_env *env)
{
	size_t	i;

	i = 0;
	while (i < point->sector->total)
	{
		if (map_add(point->sector, point->sector->elem[i].key,
			map_get(env->current_map->sectors, point->sector->elem[i].
				key)) == false)
			return (false);
		++i;
	}
	return (true);
}
