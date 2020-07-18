/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_p3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 01:51:37 by thboura           #+#    #+#             */
/*   Updated: 2020/06/07 20:53:23 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "import_internal.h"

static bool	import_wall_vector_p2(int fd, t_doom_map *map,
	t_wall *wall_tmp)
{
	t_point	**point;

	if (read(fd, wall_tmp, sizeof(t_wall_export)) < (long)sizeof(t_wall_export)
		|| (point = map_get(map->vertices, (size_t)wall_tmp->v1)) == NULL)
		return (false);
	wall_tmp->v1 = *point;
	if ((point = map_get(map->vertices,
		(size_t)wall_tmp->v2)) == NULL)
		return (false);
	wall_tmp->v2 = *point;
	return (true);
}

bool		import_wall_vector(int fd, t_doom_map *map, t_vector *wall,
	t_env *env)
{
	t_wall			wall_tmp;
	size_t			i;
	size_t			size;

	if (read(fd, &size, sizeof(t_u64)) < (long)sizeof(t_u64)
		|| !vector_init(wall, sizeof(t_wall)))
		return (false);
	i = 0;
	while (i < size)
	{
		ft_bzero(&wall_tmp, sizeof(t_wall));
		if (!import_wall_vector_p2(fd, map, &wall_tmp)
			|| !(wall_tmp.mtl_top = import_material(fd, env))
			|| !(wall_tmp.mtl_bottom = import_material(fd, env))
			|| !vector_push(wall, &wall_tmp))
		{
			mtl_destroy(&wall_tmp.mtl_top);
			mtl_destroy(&wall_tmp.mtl_bottom);
			vector_free(wall);
			return (false);
		}
		i++;
	}
	return (true);
}

static bool	init_import_sector(int fd, t_doom_map *map, t_env *env,
	t_sector **sector)
{
	if (!((*sector) = ft_memalloc(sizeof(t_sector)))
		|| read(fd, &(*sector)->id, sizeof(t_u64)) < (long)sizeof(t_u64)
		|| read(fd, &(*sector)->floor, sizeof(float)) < (long)sizeof(float)
		|| read(fd, &(*sector)->ceil, sizeof(float)) < (long)sizeof(float)
		|| read(fd, &(*sector)->has_roof, sizeof(bool)) < (long)sizeof(bool)
		|| read(fd, &(*sector)->floor_damage, sizeof(bool)) < (long)sizeof(bool)
		|| read(fd, &(*sector)->aabb, sizeof(t_aabb)) < (long)sizeof(t_aabb)
		|| !((*sector)->mtl_floor = import_material(fd, env))
		|| !((*sector)->mtl_ceil = import_material(fd, env))
		|| import_wall_vector(fd, map, &(*sector)->walls, env) == false)
	{
		free_sector(*sector);
		return (false);
	}
	return (true);
}

bool		import_sectors(int fd, t_doom_map *map, t_env *env)
{
	t_sector	*sector;
	size_t		i;
	size_t		size;

	read(fd, &size, sizeof(t_u64));
	i = 0;
	while (i < size)
	{
		if (!init_import_sector(fd, map, env, &sector))
			return (false);
		if (map_add(map->sectors, sector->id, &sector) == false)
		{
			free_sector(sector);
			return (false);
		}
		i++;
	}
	if (map->sectors->total)
		env->editor.unique_id_sectors = map->sectors->elem[
			map->sectors->total - 1].key + 1;
	return (true);
}
