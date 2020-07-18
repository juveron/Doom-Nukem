/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/23 21:25:07 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 20:37:11 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static t_doom_map	*return_error(t_doom_map *map)
{
	free_map(map);
	return (NULL);
}

t_doom_map			*create_map(char *name)
{
	t_doom_map	*map;

	if (!(map = ft_memalloc(sizeof(t_doom_map))))
		return (NULL);
	if (name && !(map->name = ft_strdup(name)))
		return (return_error(map));
	if (!(map->vertices = map_init(sizeof(t_point *)))
		|| !(map->sectors = map_init(sizeof(t_sector *)))
	|| !(vector_init(&map->pickup_objects, sizeof(t_pickup_object *))))
		return (return_error(map));
	return (map);
}

void				init_maps(t_env *env)
{
	if (!vector_init(&env->maps, sizeof(t_doom_map *)))
		throw_error("Maps initialization failed.", env);
}

void				free_map(t_doom_map *map)
{
	size_t		i;
	t_point		*point;
	t_sector	*sector;

	if (!map)
		return ;
	free(map->name);
	i = 0;
	while (i < map->vertices->total)
	{
		point = *(t_point **)map_get_index(map->vertices, i++);
		map_free(point->sector);
		free(point);
	}
	map_free(map->vertices);
	i = 0;
	while (i < map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(map->sectors, i++);
		free_sector(sector);
	}
	map_free(map->sectors);
	free_pickup_object(map);
	free(map);
}

void				free_maps(t_env *env)
{
	size_t		i;
	t_doom_map	**maps;

	i = 0;
	maps = env->maps.items;
	while (i < env->maps.total)
	{
		free_map(maps[i]);
		i++;
	}
	vector_free(&env->maps);
}
