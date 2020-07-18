/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_obj_file_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 14:58:07 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/07 14:58:07 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

size_t		count_tab(char **tab)
{
	size_t	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

bool		make_vertex_normal(char **str, t_obj_file *obj)
{
	t_vec3f		vec;

	if (count_tab(str) != 4)
		return (false);
	vec = vec3f(ft_atof(str[1]), ft_atof(str[2]), ft_atof(str[3]));
	if (!vector_push(&obj->vn, &vec))
		return (false);
	return (true);
}

bool		init_obj_file(t_obj_file *obj)
{
	vector_init(&obj->v, sizeof(t_vec3f));
	vector_init(&obj->vt, sizeof(t_vec2f));
	vector_init(&obj->vn, sizeof(t_vec3f));
	vector_init(&obj->tris, sizeof(t_triangle_index));
	if (obj->v.items == NULL || obj->vt.items == NULL || obj->vn.items == NULL
		|| obj->tris.items == NULL)
	{
		vector_free(&obj->v);
		vector_free(&obj->vt);
		vector_free(&obj->vn);
		vector_free(&obj->tris);
		return (false);
	}
	return (true);
}

static void	read_face(char **str, size_t i, t_triangle_index *tri)
{
	char				*tmp;

	tmp = str[i + 1];
	tri->v_index[i] = ft_atoi(tmp);
	tmp = ft_strchrnull(tmp, '/') + 1;
	if (*tmp == '/')
		tri->v_tex_index[i] = -1;
	else
		tri->v_tex_index[i] = ft_atoi(tmp);
	tmp = ft_strchrnull(tmp, '/') + 1;
	if (*tmp == '\0')
		tri->v_norm_index[i] = -1;
	else
		tri->v_norm_index[i] = ft_atoi(tmp);
}

bool		make_face(char **str, t_obj_file *obj)
{
	t_triangle_index	tri;
	size_t				i;

	if (count_tab(str) != 4)
		return (false);
	i = 0;
	while (i < 3)
	{
		read_face(str, i, &tri);
		i++;
	}
	tri.color = 0xFFFFFF;
	if (!vector_push(&obj->tris, &tri))
		return (false);
	return (true);
}
