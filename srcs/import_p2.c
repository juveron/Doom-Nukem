/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:43:25 by thboura           #+#    #+#             */
/*   Updated: 2020/06/13 12:52:00 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

SDL_Surface	*read_surface(int fd)
{
	int			w;
	int			h;
	SDL_Surface	*surface;
	t_u32		format;
	t_u8		depth;

	if (read(fd, &w, sizeof(int)) < (long)sizeof(int)
		|| read(fd, &h, sizeof(int)) < (long)sizeof(int)
		|| read(fd, &format, sizeof(t_u32)) < (long)sizeof(t_u32)
		|| read(fd, &depth, sizeof(t_u8)) < (long)sizeof(t_u8)
		|| !(surface = SDL_CreateRGBSurfaceWithFormat(0, w, h, depth, format)))
		return (NULL);
	if ((read(fd, surface->pixels, surface->h * surface->pitch))
		< surface->h * surface->pitch)
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	return (surface);
}

static bool	import_vertices_p3(t_u64 size_2, int fd, t_point *point)
{
	size_t		j;
	t_u64		id;

	j = 0;
	while (j < size_2)
	{
		if (read(fd, &id, sizeof(t_u64)) < (long)sizeof(t_u64)
			|| map_add(point->sector, id, &j) == false)
		{
			map_free(point->sector);
			free(point);
			return (false);
		}
		j++;
	}
	return (true);
}

static bool	import_vertices_p2(int fd, t_doom_map *map)
{
	t_point		*point;
	t_u64		size_2;

	if (!(point = ft_memalloc(sizeof(t_point)))
		|| read(fd, &point->id, sizeof(t_u64)) < (long)sizeof(t_u64)
		|| read(fd, &point->v, sizeof(t_vertex)) < (long)sizeof(t_vertex)
		|| read(fd, &size_2, sizeof(t_u64)) < (long)sizeof(t_u64)
		|| !(point->sector = map_init(sizeof(t_sector *))))
	{
		if (point)
			map_free(point->sector);
		free(point);
		return (false);
	}
	if (!import_vertices_p3(size_2, fd, point))
		return (false);
	if (map_add(map->vertices, point->id, &point) == false)
	{
		map_free(point->sector);
		free(point);
		return (false);
	}
	return (true);
}

bool		import_vertices(int fd, t_doom_map *map, t_env *env)
{
	size_t		i;
	t_u64		size;

	if (read(fd, &size, sizeof(t_u64)) < (long)sizeof(t_u64))
		return (false);
	i = 0;
	while (i < size)
	{
		if (!import_vertices_p2(fd, map))
			return (false);
		i++;
	}
	if (map->vertices->total)
		env->editor.unique_id_vertices = map->vertices->elem[
			map->vertices->total - 1].key + 1;
	return (true);
}

t_material	*import_material(int fd, t_env *env)
{
	t_material	*material;
	t_texture	**texture;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	if (read(fd, material, sizeof(t_material)) < (long)sizeof(t_material))
		return (0);
	if (material->diffuse_texture != (t_texture *)UINT64_MAX)
	{
		if (!(texture = map_get(env->texture_array,
			(size_t)material->diffuse_texture)))
		{
			free(material);
			return (NULL);
		}
		if (!mtl_add_diffuse_texture(material, *texture))
		{
			free(material);
			return (NULL);
		}
	}
	else
		material->diffuse_texture = NULL;
	return (material);
}
