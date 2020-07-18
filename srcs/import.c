/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:36:23 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 17:13:42 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "import_internal.h"
#include <fcntl.h>

bool		replace_id_sector_vertices(t_doom_map *map)
{
	size_t		i;
	size_t		j;
	t_point		*point;
	t_sector	**sector;

	i = 0;
	while (i < map->vertices->total)
	{
		point = *(t_point **)map_get_index(map->vertices, i);
		j = 0;
		while (j < point->sector->total)
		{
			if (!(sector = map_get(map->sectors, point->sector->elem[j].key)))
				return (false);
			map_add(point->sector, point->sector->elem[j].key, sector);
			j++;
		}
		i++;
	}
	return (true);
}

bool		replace_id_sector_wall(t_doom_map *map)
{
	size_t		i;
	size_t		j;
	t_sector	*sector;
	t_wall		*walls;

	i = 0;
	while (i < map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(map->sectors, i);
		walls = sector->walls.items;
		j = 0;
		while (j < sector->walls.total)
		{
			if ((size_t)walls[j].neighbor != UINT64_MAX)
				walls[j].neighbor = *(t_sector **)map_get(
					map->sectors, (size_t)walls[j].neighbor);
			else
				walls[j].neighbor = NULL;
			j++;
		}
		i++;
	}
	return (true);
}

t_doom_map	*import_map(int fd, t_env *env)
{
	t_u64		len;
	t_doom_map	*map;

	if (!(map = create_map(NULL))
		|| read(fd, &len, sizeof(len)) < (long)sizeof(len)
		|| len > 15
		|| !(map->name = ft_strnew(len))
		|| read(fd, map->name, len) < (ssize_t)len
		|| import_vertices(fd, map, env) == false
		|| import_sectors(fd, map, env) == false
		|| import_objects(fd, map) == false
		|| import_level(fd, map) == false
		|| replace_id_sector_vertices(map) == false
		|| replace_id_sector_wall(map) == false
		|| triangulate_all_sector(map) == false)
	{
		free_map(map);
		return (NULL);
	}
	return (map);
}

static bool	import_maps_p2(t_env *env, int fd, t_u64 size)
{
	t_u64		i;
	t_doom_map	*map;

	i = 0;
	while (i < size)
	{
		if (!(map = import_map(fd, env)))
		{
			close(fd);
			return (false);
		}
		if (vector_push(&env->maps, &map) == false)
		{
			close(fd);
			return (false);
		}
		i++;
	}
	env->current_map = *(t_doom_map **)vector_get(&env->maps, 0);
	close(fd);
	return (true);
}

bool		import_maps(char *pathfile, t_env *env)
{
	int			fd;
	char		tmp[6];
	t_u64		size;

	fd = open(pathfile, O_RDONLY);
	if (fd == -1)
	{
		perror("map");
		throw_error("fail to load map", env);
	}
	if ((read(fd, tmp, sizeof("DMAP") - 1) < (long)sizeof("DMAP") - 1)
		|| !ft_strnequ(tmp, "DMAP", sizeof("DMAP") - 1)
		|| (read(fd, tmp, sizeof(MAP_VERSION) - 1)
			< (long)sizeof(MAP_VERSION) - 1)
		|| !ft_strnequ(tmp, MAP_VERSION, sizeof(MAP_VERSION) - 1)
		|| !import_textures(fd, env)
		|| read(fd, &size, sizeof(t_u64)) < (long)sizeof(t_u64))
	{
		close(fd);
		return (false);
	}
	return (import_maps_p2(env, fd, size));
}
