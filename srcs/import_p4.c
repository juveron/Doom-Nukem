/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_p4.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 02:12:46 by thboura           #+#    #+#             */
/*   Updated: 2020/06/12 14:54:23 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "import_internal.h"

static bool	import_textures_p2(int fd, t_env *env)
{
	t_u16		size2;
	t_texture	*texture;

	if (!(texture = ft_memalloc(sizeof(t_texture)))
		|| read(fd, &size2, sizeof(t_u16)) < (long)sizeof(t_u16)
		|| !(texture->name = ft_strnew(size2))
		|| read(fd, texture->name, size2) < (ssize_t)size2
		|| read(fd, &texture->id, sizeof(t_u64)) < (long)sizeof(t_u64)
		|| !(texture->surface = read_surface(fd))
		|| !vector_init(&texture->materials, sizeof(t_material *))
		|| !map_add(env->texture_array, texture->id, &texture))
	{
		if (texture)
		{
			free(texture->name);
			SDL_FreeSurface(texture->surface);
			vector_free(&texture->materials);
		}
		free(texture);
		return (false);
	}
	return (true);
}

bool		import_textures(int fd, t_env *env)
{
	size_t		size;
	size_t		i;

	if (read(fd, &size, sizeof(t_u64)) < (long)sizeof(t_u64))
		return (false);
	i = 0;
	while (i < size)
	{
		if (!import_textures_p2(fd, env))
			return (false);
		i++;
	}
	if (env->texture_array->total == 0)
		env->texture_unique_id = 0;
	else
		env->texture_unique_id = env->texture_array->elem[
			env->texture_array->total - 1].key + 1;
	return (true);
}

bool		import_level(int fd, t_doom_map *map)
{
	if (read(fd, &map->level, sizeof(t_level_param))
		< (long)sizeof(t_level_param))
		return (false);
	return (true);
}

bool		import_objects(int fd, t_doom_map *map)
{
	t_u64			size;
	size_t			i;
	t_pickup_object	**objs;

	if (read(fd, &size, sizeof(t_u64)) < (long)sizeof(t_u64))
		return (false);
	vector_free(&map->pickup_objects);
	if (!vector_init_n(&map->pickup_objects, sizeof(t_pickup_object *), size))
		return (false);
	objs = map->pickup_objects.items;
	i = 0;
	while (i < size)
	{
		if (!(objs[i] = malloc(sizeof(t_pickup_object)))
			|| read(fd, objs[i], sizeof(t_pickup_object))
			< (long)sizeof(t_pickup_object))
		{
			free_pickup_object(map);
			return (false);
		}
		++i;
	}
	return (true);
}

bool		import_triangle(int fd, t_vector *triangle)
{
	size_t		i;
	t_u64		size;
	t_triangle	tri;

	if (!vector_init(triangle, sizeof(t_triangle)))
		return (false);
	i = 0;
	if (read(fd, &size, sizeof(unsigned long)) < (long)sizeof(unsigned long))
	{
		vector_free(triangle);
		return (false);
	}
	while (i < size)
	{
		if (read(fd, &tri, sizeof(t_triangle))
			< (long)sizeof(t_triangle)
			|| !vector_push(triangle, &tri))
		{
			vector_free(triangle);
			return (false);
		}
		i++;
	}
	return (true);
}
