/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_valid_map.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 11:53:34 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/12 13:24:52 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	check_level(t_doom_map *map)
{
	return (map->level.start.available && map->level.end.available);
}

bool		check_valid_map(t_env *env)
{
	t_doom_map	**maps;
	size_t		i;

	maps = env->maps.items;
	i = 0;
	while (i < env->maps.total)
	{
		if (!check_level(maps[i]))
		{
			ft_printf("{red}Map need start and end level.{end}\n");
			return (false);
		}
		++i;
	}
	return (true);
}
