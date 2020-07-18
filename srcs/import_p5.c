/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_p5.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/12 20:31:13 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/12 20:31:13 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool		triangulate_all_sector(t_doom_map *map)
{
	t_sector	*sector;
	size_t		i;

	i = 0;
	while (i < map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(map->sectors, i);
		if (!triangulate_sector(sector))
			return (false);
		++i;
	}
	return (true);
}
