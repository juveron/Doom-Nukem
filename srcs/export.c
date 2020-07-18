/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:03:10 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/06 03:21:17 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_internal.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static bool	export_material(int fd, t_material *material)
{
	t_material	tmp;

	tmp = *material;
	if (material->diffuse_texture)
		tmp.diffuse_texture = (t_texture *)tmp.diffuse_texture->id;
	else
		tmp.diffuse_texture = (t_texture *)UINT64_MAX;
	if (write(fd, &tmp, sizeof(t_material)) == -1)
		return (false);
	return (true);
}

static bool	export_wall_vector(int fd, t_vector *wall)
{
	t_wall_export	wall_export;
	t_wall			*walls;
	size_t			i;

	walls = wall->items;
	if (write(fd, &wall->total, sizeof(t_u64)) == -1)
		return (false);
	i = 0;
	while (i < wall->total)
	{
		ft_memcpy(&wall_export, &walls[i], sizeof(t_wall_export));
		wall_export.v1_id = walls[i].v1->id;
		wall_export.v2_id = walls[i].v2->id;
		if (walls[i].neighbor)
			wall_export.neighbor = walls[i].neighbor->id;
		else
			wall_export.neighbor = UINT64_MAX;
		if (write(fd, &wall_export, sizeof(t_wall_export)) == -1
			|| export_material(fd, walls[i].mtl_top) == false
			|| export_material(fd, walls[i].mtl_bottom) == false)
			return (false);
		i++;
	}
	return (true);
}

static bool	export_sectors(int fd, t_doom_map *map)
{
	t_sector			*sector;
	size_t				i;

	if (write(fd, &map->sectors->total, sizeof(t_u64)) == -1)
		return (false);
	i = 0;
	while (i < map->sectors->total)
	{
		sector = *(t_sector **)map_get_index(map->sectors, i);
		if (write(fd, &sector->id, sizeof(t_u64)) == -1
			|| write(fd, &sector->floor, sizeof(float)) == -1
			|| write(fd, &sector->ceil, sizeof(float)) == -1
			|| write(fd, &sector->has_roof, sizeof(bool)) == -1
			|| write(fd, &sector->floor_damage, sizeof(bool)) == -1
			|| write(fd, &sector->aabb, sizeof(t_aabb)) == -1
			|| export_material(fd, sector->mtl_floor) == false
			|| export_material(fd, sector->mtl_ceil) == false
			|| export_wall_vector(fd, &sector->walls) == false)
			return (false);
		++i;
	}
	return (true);
}

static bool	export_map(int fd, t_doom_map *map)
{
	if (write(fd, &(t_u64){ft_strlen(map->name)}, sizeof(t_u64)) == -1
		|| write(fd, map->name, ft_strlen(map->name)) == -1
		|| export_vertices(fd, map) == false
		|| export_sectors(fd, map) == false
		|| export_objects(fd, map) == false
		|| export_level(fd, map) == false)
		return (false);
	return (true);
}

bool		export_map_file(char *pathfile, t_env *env)
{
	int					fd;
	size_t				i;
	t_doom_map			**maps;

	fd = open(pathfile, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU);
	if (fd == -1 || write(fd, "DMAP", sizeof("DMAP") - 1) == -1
		|| write(fd, MAP_VERSION, sizeof(MAP_VERSION) - 1) == -1
		|| export_textures(fd, env) == false
		|| write(fd, &env->maps.total, sizeof(t_u64)) == -1)
		return (exit_export_map(fd));
	i = 0;
	maps = env->maps.items;
	while (i < env->maps.total)
	{
		export_map(fd, maps[i]);
		i++;
	}
	close(fd);
	return (true);
}
