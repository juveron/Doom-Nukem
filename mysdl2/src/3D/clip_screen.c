/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clip_screen.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/06 18:03:31 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/06 18:03:31 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "clipping_internal.h"
#include "rasterizer.h"

static void	swap_pointer(t_triangle_raster **p1, t_triangle_raster **p2)
{
	t_triangle_raster	*tmp;

	tmp = *p1;
	*p1 = *p2;
	*p2 = tmp;
}

static void	clip_screen_p2(t_clip_screen_internal *clip)
{
	int		n_tri;
	int		k;

	k = 0;
	while (k < clip->j)
	{
		if (clip->i == 0)
			n_tri = triangle_clip_plane(&clip->planes[0], &clip->in[k],
										clip->out + clip->last_size);
		else if (clip->i == 1)
			n_tri = triangle_clip_plane(&clip->planes[1], &clip->in[k],
										clip->out + clip->last_size);
		else if (clip->i == 2)
			n_tri = triangle_clip_plane(&clip->planes[2], &clip->in[k],
										clip->out + clip->last_size);
		else
			n_tri = triangle_clip_plane(&clip->planes[3], &clip->in[k],
										clip->out + clip->last_size);
		clip->last_size += n_tri;
		++k;
	}
}

static void	init_planes(t_clip_screen_internal *clip)
{
	clip->planes[0] = (t_plane){(t_vec4f){0.f, 0.f, 0.f, 1},
			(t_vec4f){0.f, 1.f, 0.f, 1}};
	clip->planes[1] = (t_plane){(t_vec4f){0.f, HEIGHT_ - 1, 0.f, 1},
			(t_vec4f){0.f, -1.f, 0.f, 1}};
	clip->planes[2] = (t_plane){(t_vec4f){0.f, 0.f, 0.f, 1},
			(t_vec4f){1.f, 0.f, 0.f, 1}};
	clip->planes[3] = (t_plane){(t_vec4f){WIDTH_ - 1, 0.f, 0.f, 1},
			(t_vec4f){-1.f, 0.f, 0.f, 1}};
}

static bool	add_all_triangle(t_triangle_raster clipped_triangle[16],
		size_t size)
{
	t_context_3d	*context_3d;
	size_t			i;

	i = (size_t)-1;
	context_3d = get_context()->context_3d;
	while (++i < size)
	{
		if (edge_function(&clipped_triangle[i].vertex[0].v,
			&clipped_triangle[i].vertex[1].v,
			&clipped_triangle[i].vertex[2].v) == 0)
			continue;
		context_3d->n_tri++;
		if (!add_triangle_to_tiles(&clipped_triangle[i],
			context_3d->material))
			return (false);
	}
	return (true);
}

void		clip_screen(t_triangle_raster *triangle)
{
	t_clip_screen_internal	clip;

	init_planes(&clip);
	clip.array1[0] = *triangle;
	clip.last_size = 1;
	clip.i = 0;
	clip.in = clip.array1;
	clip.out = clip.array2;
	while (clip.i < 4)
	{
		clip.j = clip.last_size;
		clip.last_size = 0;
		clip_screen_p2(&clip);
		if (clip.last_size == 0)
			return ;
		swap_pointer(&clip.in, &clip.out);
		clip.i++;
	}
	if (!add_all_triangle(clip.in, clip.last_size))
		return ;
}
