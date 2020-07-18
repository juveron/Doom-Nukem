/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 12:51:00 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/27 09:28:38 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_map.h"
#include "libft_mem.h"

t_map	*map_init(size_t sizeof_elem)
{
	t_map	*map;

	if (!(map = malloc(sizeof(t_map))))
		return (NULL);
	map->capacity = MAP_INIT_CAPACITY;
	map->total = 0;
	if (!(map->elem = (t_map_elem *)malloc(sizeof(t_map_elem)
		* map->capacity)))
	{
		free(map);
		return (NULL);
	}
	map->sizeof_elem = sizeof_elem;
	return (map);
}

size_t	map_total(t_map *map)
{
	if (!map)
		return (0);
	return (map->total);
}

void	map_free(t_map *map)
{
	size_t	i;

	i = 0;
	if (!map)
		return ;
	while (i < map->total)
	{
		free(map->elem[i].data);
		i++;
	}
	free(map->elem);
	free(map);
}

bool	map_resize(t_map *map, size_t capacity)
{
	t_map_elem	*elem;

	if (capacity < map->capacity)
	{
		if (!(elem = (t_map_elem *)malloc(capacity * sizeof(t_map_elem))))
		{
			ft_memdel((void **)&map->elem);
			return (false);
		}
		ft_memcpy(elem, map->elem, capacity * sizeof(t_map_elem));
		ft_bzero(elem + map->total, map->capacity - map->total);
		free(map->elem);
	}
	else
		elem = (t_map_elem *)ft_memrealloc(map->elem, sizeof(t_map_elem)
			* map->capacity, sizeof(t_map_elem) * capacity);
	if (!elem)
	{
		ft_memdel((void **)&map->elem);
		return (false);
	}
	map->elem = elem;
	map->capacity = capacity;
	return (true);
}

void	*map_get_index(t_map *map, t_u64 index)
{
	if (index >= map->total)
		return (NULL);
	return (map->elem[index].data);
}
