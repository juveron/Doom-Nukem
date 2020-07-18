/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 15:18:07 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/27 16:22:45 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_map.h"
#include "libft.h"

static int	return_value(t_map *map, size_t key, size_t high, size_t low)
{
	if (key <= map->elem[high].key)
		return (high);
	if (low < map->total && key <= map->elem[low].key)
		return (low);
	return (map->total);
}

int			map_binary_search(t_map *map, size_t key)
{
	size_t	high;
	size_t	low;
	size_t	mid;

	if (map->total == 0)
		return (0);
	high = map->total - 1;
	low = 0;
	while (low <= high)
	{
		mid = (high + low) / 2;
		if (map->elem[mid].key == key)
			return (mid);
		if (key < map->elem[mid].key)
		{
			if (mid == 0)
				return (0);
			high = mid - 1;
		}
		else
			low = mid + 1;
	}
	return (return_value(map, key, high, low));
}

static bool	map_add_internal(t_map *map, size_t key, void *data,
	size_t elem_index)
{
	size_t	i;

	if (map->capacity == map->total)
	{
		if (!map_resize(map, map->capacity * 2))
			return (false);
	}
	i = map->total++;
	while (i >= elem_index + 1)
	{
		map->elem[i] = map->elem[i - 1];
		i--;
	}
	map->elem[elem_index].key = key;
	if (!(map->elem[elem_index].data = malloc(map->sizeof_elem)))
	{
		map_free(map);
		return (false);
	}
	ft_memcpy(map->elem[elem_index].data, data, map->sizeof_elem);
	return (true);
}

bool		map_add(t_map *map, size_t key, void *data)
{
	size_t	elem_index;

	elem_index = map_binary_search(map, key);
	if (elem_index != map->total && map->elem[elem_index].key == key)
		ft_memcpy(map->elem[elem_index].data, data, map->sizeof_elem);
	else
		return (map_add_internal(map, key, data, elem_index));
	return (true);
}

void		*map_get(t_map *map, size_t key)
{
	size_t	index;

	index = map_binary_search(map, key);
	if (index == map->total || key != map->elem[index].key)
		return (NULL);
	else
		return (map->elem[index].data);
}
