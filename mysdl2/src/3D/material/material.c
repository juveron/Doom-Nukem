/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/15 13:51:53 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/13 15:20:29 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

t_material	*mtl_clone(t_material *src)
{
	t_material	*dest;

	if (src == NULL)
		return (NULL);
	if (!(dest = ft_memalloc(sizeof(t_material))))
		return (NULL);
	*dest = *src;
	if (src->diffuse_texture)
	{
		if (!mtl_add_diffuse_texture(dest, src->diffuse_texture))
		{
			free(dest);
			return (NULL);
		}
	}
	return (dest);
}

t_material	*mtl_create(void)
{
	t_material	*material;
	t_vec2f		angle;

	if (!(material = ft_memalloc(sizeof(t_material))))
		return (NULL);
	angle = vec2f_from_angle(radian(material->angle));
	material->step.x = angle.x;
	material->step.y = angle.y;
	material->diffuse_color = 0xA6A6A6;
	material->uv_scale.x = 1;
	material->uv_scale.y = 1;
	material->use_advenced_movement = true;
	return (material);
}

void		mtl_destroy(t_material **material)
{
	if (*material == NULL)
		return ;
	if ((*material)->diffuse_texture)
		remove_material_from_texture((*material)->diffuse_texture, *material);
	free(*material);
	*material = NULL;
}
