/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_obj_file.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 09:31:01 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/11 10:16:15 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "open_obj_internal.h"
#include <fcntl.h>
#include <stdio.h>

t_mesh	*init_convert(t_obj_file *obj, t_obj_utils *p)
{
	t_mesh	*mesh;

	if (!(mesh = (t_mesh *)ft_memalloc(sizeof(t_mesh))))
		return (NULL);
	if (!vector_init(&mesh->vertex, sizeof(t_vertex)))
	{
		free(mesh);
		return (NULL);
	}
	if (!vector_init(&mesh->render_objects, sizeof(t_render_object *)))
	{
		vector_free(&mesh->vertex);
		free(mesh);
		return (NULL);
	}
	p->p_v = obj->v.items;
	p->p_vt = obj->vt.items;
	p->p_vn = obj->vn.items;
	p->p_tris = obj->tris.items;
	return (mesh);
}

bool	obj_to_mesh_p2(t_mesh *mesh, t_obj_file *obj, char *mesh_name)
{
	if (!(mesh->default_material = mtl_create()))
		return (free_mesh_and_obj(mesh, obj));
	free_obj(obj);
	if (!(mesh->name = ft_strdup(mesh_name)))
		return (free_mesh_and_obj(mesh, obj));
	return (true);
}

t_mesh	*obj_to_mesh(t_obj_file *obj, char *mesh_name)
{
	t_mesh		*mesh;
	t_obj_utils	p;
	t_vertex	vertex;
	size_t		i;
	size_t		j;

	if (!(mesh = init_convert(obj, &p)))
		return (NULL);
	i = 0;
	while (i < obj->tris.total)
	{
		j = 0;
		while (j < 3)
		{
			vertex.v = p.p_v[p.p_tris[i].v_index[j] - 1];
			vertex.v_texture = p.p_vt[p.p_tris[i].v_tex_index[j] - 1];
			if (!vector_push(&mesh->vertex, &vertex))
				return (free_mesh_and_obj(mesh, obj));
			j++;
		}
		i++;
	}
	if (!obj_to_mesh_p2(mesh, obj, mesh_name))
		return (free_mesh_and_obj(mesh, obj));
	return (mesh);
}

bool	open_obj_file_p2(char *line, int fd, t_obj_file *obj)
{
	char		**str;
	bool		error;

	error = true;
	str = ft_strsplit(line, ' ');
	if (ft_strequ(str[0], "v"))
		error = make_vertex(str, obj);
	else if (ft_strequ(str[0], "vt"))
		error = make_vertex_texture(str, obj);
	else if (ft_strequ(str[0], "f"))
		error = make_face(str, obj);
	ft_memdel((void **)&line);
	ft_freetab((void ***)&str);
	if (!error)
	{
		close(fd);
		return (free_obj(obj));
	}
	return (true);
}

t_mesh	*open_obj_file(char *filepath, char *mesh_name)
{
	char		*line;
	int			fd;
	t_obj_file	obj;
	int			ret;

	if (!init_obj_file(&obj))
		return (NULL);
	if ((fd = open_file(filepath)) != -1)
	{
		while ((ret = get_next_line(fd, &line)) > 0)
		{
			if (!open_obj_file_p2(line, fd, &obj))
				return (NULL);
		}
		close(fd);
		if (ret == -1)
			return (free_obj(&obj));
	}
	else
		return (free_obj(&obj));
	return (obj_to_mesh(&obj, mesh_name));
}
