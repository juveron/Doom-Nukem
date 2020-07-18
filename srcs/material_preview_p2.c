/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_preview_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:30:09 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 17:32:35 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

t_u32			get_texture(SDL_Surface *texture, t_vec2f *uv)
{
	int	x;
	int	y;

	x = (uv->x - floorf(uv->x)) * (texture->w - 1);
	y = (1 - (uv->y - floorf(uv->y))) * (texture->h - 1);
	return (((t_u32 *)texture->pixels)[y * texture->w + x]);
}

static void		draw_preview_p2(t_gui_material_preview *mat_prev,
	t_vec2f *uv, t_vec2f *step, int y)
{
	int	x;

	x = 0;
	while (x < mat_prev->surface->w)
	{
		uv->x += step->x * mat_prev->material->uv_scale.x;
		uv->y += step->y * mat_prev->material->uv_scale.y;
		((t_u32 *)mat_prev->surface->pixels)[x + y
			* mat_prev->surface->w] = get_texture(mat_prev->material->
			diffuse_texture->surface, uv);
		x++;
	}
}

void			draw_preview(t_gui_material_preview *mat_prev)
{
	int		y;
	t_vec2f	uv;
	t_vec2f	angle;
	t_vec2f	step;
	t_vec2f	uv2;

	uv = mat_prev->material->uv_pos;
	angle = vec2f_from_angle(radian(mat_prev->material->angle));
	step.x = angle.x / (float)mat_prev->surface->w;
	step.y = angle.y / (float)mat_prev->surface->h;
	y = 0;
	while (y < mat_prev->surface->h)
	{
		uv2.x = uv.x;
		uv2.y = uv.y;
		draw_preview_p2(mat_prev, &uv, &step, y);
		uv.x = uv2.x - step.y * mat_prev->material->uv_scale.x;
		uv.y = uv2.y + step.x * mat_prev->material->uv_scale.y;
		y++;
	}
}

bool			draw_mat_prev_func(void *param)
{
	t_gui_material_preview	*mat_prev;

	mat_prev = param;
	if (!mat_prev->material)
		draw_rectangle((SDL_Rect){0, 0, mat_prev->component.rect.w,
			mat_prev->component.rect.h}, 0xFFFFFF,
			mat_prev->component.surface);
	else if (mat_prev->material->diffuse_texture != NULL)
	{
		if (mat_prev->need_redraw)
		{
			mat_prev->need_redraw = false;
			draw_preview(mat_prev);
		}
		SDL_BlitSurface(mat_prev->surface, NULL,
			mat_prev->component.surface, &(SDL_Rect){0, 0,
			mat_prev->component.rect.w, mat_prev->component.rect.h});
	}
	else
		draw_rectangle((SDL_Rect){0, 0, mat_prev->component.rect.w,
		mat_prev->component.rect.h},
			mat_prev->material->diffuse_color << 8 | 0xFF,
			mat_prev->component.surface);
	return (true);
}

bool			update_mat_prev_func(void *param)
{
	(void)param;
	return (true);
}
