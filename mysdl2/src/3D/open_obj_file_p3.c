/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_obj_file_p3.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 14:58:10 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/07 14:58:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_obj_internal.h"
#include <fcntl.h>

int		open_file(char *path)
{
	int			fd;

	if ((fd = open(path, O_RDONLY)) == -1)
	{
		perror(path);
		return (-1);
	}
	return (fd);
}

void	*free_obj(t_obj_file *obj)
{
	vector_free(&obj->v);
	vector_free(&obj->vt);
	vector_free(&obj->vn);
	vector_free(&obj->tris);
	return (NULL);
}

void	*free_mesh_and_obj(t_mesh *mesh, t_obj_file *obj)
{
	destroy_mesh(&mesh);
	return (free_obj(obj));
}

bool	make_vertex(char **str, t_obj_file *obj)
{
	t_vec4f		vec;

	if (count_tab(str) != 4)
		return (false);
	vec = vec4f(ft_atof(str[1]), ft_atof(str[2]), ft_atof(str[3]), 1);
	if (!vector_push(&obj->v, &vec))
		return (false);
	return (true);
}

bool	make_vertex_texture(char **str, t_obj_file *obj)
{
	t_vec3f		vec;

	if (count_tab(str) != 3)
		return (false);
	vec = vec3f(ft_atof(str[1]), ft_atof(str[2]), 1);
	if (!vector_push(&obj->vt, &vec))
		return (false);
	return (true);
}
