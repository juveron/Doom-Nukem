/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 13:46:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 12:12:28 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

bool		add_material_to_texture(t_texture *texture, t_material *material)
{
	return (vector_push(&texture->materials, &material));
}

bool		remove_material_from_texture(t_texture *texture,
	t_material *material)
{
	size_t		i;
	t_material	**materials;

	if (texture == NULL)
		return (true);
	i = 0;
	materials = texture->materials.items;
	while (i < texture->materials.total)
	{
		if (materials[i] == material)
		{
			if (vector_delete(&texture->materials, i) == false)
				return (false);
			return (true);
		}
		i++;
	}
	return (true);
}

t_texture	*create_texture(const char *name, SDL_Surface *surface,
	const t_u64 id)
{
	t_texture	*texture;

	if (!(texture = ft_memalloc(sizeof(t_texture))))
	{
		SDL_FreeSurface(surface);
		return (NULL);
	}
	if (!(texture->name = ft_strdup(name))
		|| !(texture->surface = SDL_ConvertSurfaceFormat(surface,
		SDL_PIXELFORMAT_RGB888, 0))
		|| !vector_init(&texture->materials, sizeof(t_material *)))
	{
		SDL_FreeSurface(surface);
		free(texture->name);
		free(texture);
		return (NULL);
	}
	texture->id = id;
	SDL_FreeSurface(surface);
	return (texture);
}

void		destroy_texture(t_texture **texture)
{
	size_t		i;
	t_material	**materials;

	if (*texture == NULL)
		return ;
	free((*texture)->name);
	SDL_FreeSurface((*texture)->surface);
	materials = (*texture)->materials.items;
	i = 0;
	while (i < (*texture)->materials.total)
	{
		materials[i]->diffuse_texture = NULL;
		++i;
	}
	vector_free(&(*texture)->materials);
	free(*texture);
	*texture = NULL;
}
