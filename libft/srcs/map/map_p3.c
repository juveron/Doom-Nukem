/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_p3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/22 10:40:09 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/27 16:06:41 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal/libft_map_internal.h"
#include "libft.h"

bool	map_delete(t_map *map, size_t key)
{
	size_t	i;
	size_t	elem_index;

	elem_index = map_binary_search(map, key);
	if (elem_index == map->total)
		return (true);
	if (map->elem[elem_index].key != key)
		return (true);
	ft_memdel(&map->elem[elem_index].data);
	map->elem[elem_index] = (t_map_elem){.key = 0, .data = 0};
	i = elem_index;
	while (i < map->total - 1)
	{
		map->elem[i] = map->elem[i + 1];
		i++;
	}
	--map->total;
	if (map->total > 0 && map->total == map->capacity / 4)
	{
		if (!map_resize(map, map->capacity / 2))
			return (false);
	}
	return (true);
}

bool	map_clone(t_map **dst, t_map *src)
{
	size_t	i;

	i = 0;
	if (!(*dst = map_init(src->sizeof_elem)))
		return (false);
	if (!map_resize(*dst, src->capacity))
	{
		map_free(*dst);
		return (false);
	}
	while (i < src->total)
	{
		(*dst)->elem[i].key = src->elem[i].key;
		if (!((*dst)->elem[i].data = malloc(src->sizeof_elem)))
		{
			map_free(*dst);
			return (false);
		}
		ft_memmove((*dst)->elem[i].data, src->elem[i].data, src->sizeof_elem);
		i++;
	}
	(*dst)->total = src->total;
	return (true);
}
