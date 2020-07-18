/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mtl_diffuse.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/16 13:58:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/04/15 02:36:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool		mtl_add_diffuse_texture(t_material *material,
	t_texture *diffuse_texture)
{
	if (!material || !diffuse_texture)
		return (true);
	material->diffuse_texture = diffuse_texture;
	if (!add_material_to_texture(diffuse_texture, material))
		return (false);
	return (true);
}

bool		mtl_remove_diffuse_texture(t_material *material)
{
	if (material->diffuse_texture)
	{
		if (!remove_material_from_texture(material->diffuse_texture, material))
			return (false);
		material->diffuse_texture = NULL;
	}
	return (true);
}

void		mtl_change_diffuse_color(t_material *material, t_u32 diffuse_color)
{
	material->diffuse_color = diffuse_color;
}
