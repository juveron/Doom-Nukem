/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_p2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:03:10 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/06 03:21:23 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_internal.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

static bool	write_surface(int fd, SDL_Surface *surface)
{
	if (write(fd, &surface->w, sizeof(int)) == -1
		|| write(fd, &surface->h, sizeof(int)) == -1
		|| write(fd, &surface->format->format, sizeof(t_u32)) == -1
		|| write(fd, &surface->format->BitsPerPixel, sizeof(t_u8)) == -1
		|| write(fd, surface->pixels, surface->h * surface->pitch) == -1)
		return (false);
	return (true);
}

bool		export_textures(int fd, t_env *env)
{
	size_t		i;
	t_texture	*tmp;

	if (write(fd, &env->texture_array->total, sizeof(t_u64)) == -1)
		return (false);
	i = 0;
	while (i < env->texture_array->total)
	{
		tmp = *(t_texture **)map_get_index(env->texture_array, i);
		if (write(fd, &(t_u16){ft_strlen(tmp->name)}, sizeof(t_u16)) == -1
			|| write(fd, tmp->name, ft_strlen(tmp->name)) == -1
			|| write(fd, &tmp->id, sizeof(t_u64)) == -1
			|| write_surface(fd, tmp->surface) == false)
			return (false);
		i++;
	}
	return (true);
}

bool		export_vertices(int fd, t_doom_map *map)
{
	t_point		*point;
	t_sector	*sector;
	size_t		i;
	size_t		j;

	if (write(fd, &map->vertices->total, sizeof(t_u64)) == -1)
		return (false);
	i = 0;
	while (i < map->vertices->total)
	{
		point = *(t_point **)map_get_index(map->vertices, i);
		if (write(fd, &point->id, sizeof(t_u64)) == -1
			|| write(fd, &point->v, sizeof(t_vertex)) == -1
			|| write(fd, &point->sector->total, sizeof(t_u64)) == -1)
			return (false);
		j = 0;
		while (j < point->sector->total)
		{
			sector = *(t_sector **)map_get_index(point->sector, j++);
			if (write(fd, &sector->id, sizeof(t_u64)) == -1)
				return (false);
		}
		i++;
	}
	return (true);
}

bool		export_level(int fd, t_doom_map *map)
{
	if (write(fd, &map->level, sizeof(t_level_param)) == -1)
		return (false);
	return (true);
}

bool		export_triangle_vector(int fd, t_vector *triangle)
{
	size_t		i;
	t_triangle	*tri;

	tri = triangle->items;
	i = 0;
	if (write(fd, &triangle->total, sizeof(t_u64)) == -1)
		return (false);
	while (i < triangle->total)
	{
		if (write(fd, &tri[i], sizeof(t_triangle)) == -1)
			return (false);
		i++;
	}
	return (true);
}
