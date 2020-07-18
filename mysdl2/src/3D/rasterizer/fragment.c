/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fragment.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 11:09:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/06 11:09:52 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"
#include "mysdl2.h"

static t_u32	get_texture(const SDL_Surface *surface, const t_vec2f *uv)
{
	int		x;
	int		y;
	int		index;
	t_u32	color;

	x = (uv->x - floorf(uv->x)) * (surface->w - 1);
	y = (1 - (uv->y - floorf(uv->y))) * (surface->h - 1);
	index = y * surface->w + x;
	color = ((t_u32 *)surface->pixels)[index];
	return (color);
}

static void		get_coord_rotated(t_material *material, t_vec2f *tex_coord,
		t_fragment_data *data)
{
	if (material->uv_scale.x == 1.f)
		tex_coord->x = material->uv_pos.x - material->step.y
			* data->tex_coord.y + material->step.x * data->tex_coord.x;
	else
		tex_coord->x = material->uv_pos.x - material->step.y
			* material->uv_scale.x * data->tex_coord.y
			+ material->step.x * data->tex_coord.x
			* material->uv_scale.x;
	if (material->uv_scale.y == 1.f)
		tex_coord->y = material->uv_pos.y + material->step.x
			* data->tex_coord.y + material->step.y * data->tex_coord.x;
	else
		tex_coord->y = material->uv_pos.y + material->step.x
			* material->uv_scale.y * data->tex_coord.y
			+ material->step.y * data->tex_coord.x
			* material->uv_scale.y;
}

static void		get_coord_not_rotated(t_material *material, t_vec2f *tex_coord,
		t_fragment_data *data)
{
	if (material->uv_scale.x == 1.f)
		tex_coord->x = material->uv_pos.x + data->tex_coord.x;
	else
		tex_coord->x = material->uv_pos.x + data->tex_coord.x
			* material->uv_scale.x;
	if (material->uv_scale.y == 1.f)
		tex_coord->y = material->uv_pos.y + data->tex_coord.y;
	else
		tex_coord->y = material->uv_pos.y + data->tex_coord.y
			* material->uv_scale.y;
}

void			fragment_function(t_fragment_data *data)
{
	t_vec2f		tex_coord;
	t_material	*material;

	material = data->material;
	if (data->debug_clip && data->color != 0)
		data->frag_color = data->color;
	else if (data->material->diffuse_texture != NULL)
	{
		if (data->material->use_advenced_movement)
		{
			if (material->step.x == 1.f)
				get_coord_not_rotated(material, &tex_coord, data);
			else
				get_coord_rotated(material, &tex_coord, data);
		}
		else
			tex_coord = data->tex_coord;
		data->frag_color = get_texture(material->diffuse_texture->surface,
				&tex_coord);
	}
	else
		data->frag_color = material->diffuse_color;
}
