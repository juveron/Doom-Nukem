/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:06:55 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/04 17:06:56 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_3d(t_env *env)
{
	t_context	*context;

	context = get_context();
	env->camera.name = "player_camera";
	env->camera.m_proj = matrix_perspective_fov(120, (float)WIDTH
		/ (float)HEIGHT, 0.1f, 1000.f);
	ft_bzero(&env->camera.transform, sizeof(t_transform));
	env->camera.transform.position.z = 30;
	if (!(env->camera.depth_buffer = malloc(sizeof(float) * WIDTH * HEIGHT)))
		return (false);
	env->camera.m_proj_inv = matrix_invert2(env->camera.m_proj);
	context->context_3d->render_screen.height = HEIGHT;
	context->context_3d->render_screen.width = WIDTH;
	context->context_3d->render_screen.surface = env->framebuffer;
	context->context_3d->render_screen.active_camera = &env->camera;
	env->global_option.mouse_sensibility = .3f;
	if (!build_tile_array()
		|| !load_global_mesh(env)
		|| !init_rasterizer_worker())
		return (false);
	env->time_scale = 1.f;
	return (true);
}
