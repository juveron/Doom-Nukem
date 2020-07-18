/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 18:21:34 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 18:21:34 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void				free_pickup_object(t_doom_map *map)
{
	size_t			i;
	t_pickup_object	**pickup;

	i = 0;
	pickup = map->pickup_objects.items;
	while (i < map->pickup_objects.total)
	{
		free(pickup[i]);
		++i;
	}
	vector_free(&map->pickup_objects);
}
