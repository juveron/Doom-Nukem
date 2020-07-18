/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_p3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 17:59:05 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 18:58:56 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "export_internal.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

bool	export_objects(int fd, t_doom_map *map)
{
	t_pickup_object **objs;
	size_t			i;

	if (write(fd, &map->pickup_objects.total, sizeof(t_u64)) == -1)
		return (false);
	objs = map->pickup_objects.items;
	i = 0;
	while (i < map->pickup_objects.total)
	{
		if (write(fd, objs[i], sizeof(t_pickup_object)) == -1)
			return (false);
		++i;
	}
	return (true);
}

bool	exit_export_map(int fd)
{
	if (fd > -1)
		close(fd);
	perror("export_map");
	return (false);
}
