/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   levels.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/10 09:01:49 by thboura           #+#    #+#             */
/*   Updated: 2020/07/16 13:18:14 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	init_levels_manager(t_env *env, t_levels_manager *levels_manager)
{
	levels_manager->editor.active = false;
	levels_manager->editor.move_handler.active = false;
	if (!(levels_manager->start_surface = TTF_RenderText_Blended(env->fonts.
		deja_vu_sans_momo_16, "Start", (SDL_Color){255, 255, 255, 0})))
		return (false);
	if (!(levels_manager->end_surface = TTF_RenderText_Blended(env->fonts.
		deja_vu_sans_momo_16, "End", (SDL_Color){255, 255, 255, 0})))
	{
		free_levels_manager(env);
		return (false);
	}
	return (true);
}

bool	init_levels_manager_3d(t_env *env)
{
	SDL_Surface	*surface;

	if (!(surface = import_tga("./assets/end.tga", false))
		|| !(env->levels_manager.end = create_texture("end", surface, 0))
		|| !(surface = import_tga("./assets/start.tga", false))
		|| !(env->levels_manager.start = create_texture("start", surface, 0))
		|| !(env->levels_manager.material_start = mtl_create())
		|| !(env->levels_manager.material_end = mtl_create())
		|| !(env->levels_manager.start_obj = create_render_object("Start point",
			env->global_mesh.cube_mesh, true,
			env->levels_manager.material_start))
		|| !(env->levels_manager.end_obj = create_render_object("End point",
			env->global_mesh.cube_mesh, true,
			env->levels_manager.material_end)))
	{
		free_levels_manager_3d(env);
		return (false);
	}
	if (!mtl_add_diffuse_texture(env->levels_manager.material_start,
		env->levels_manager.start)
		|| !mtl_add_diffuse_texture(env->levels_manager.material_end,
		env->levels_manager.end))
		return (false);
	load_level_position(env);
	return (true);
}

void	load_level_position(t_env *env)
{
	env->levels_manager.start_obj->transform.scale = (t_vec3f){0.1f, 0.1f,
		0.1f};
	env->levels_manager.end_obj->transform.scale = (t_vec3f){0.1f, 0.1f, 0.1f};
	if (env->current_map->level.start.available)
		env->levels_manager.start_obj->transform.position = env->current_map->
			level.start.position;
	if (env->current_map->level.end.available)
		env->levels_manager.end_obj->transform.position = env->current_map->
			level.end.position;
}

void	free_levels_manager_3d(t_env *env)
{
	ft_printf("Free levels manager 3D\n");
	destroy_render_object(&env->levels_manager.end_obj);
	destroy_render_object(&env->levels_manager.start_obj);
	mtl_destroy(&env->levels_manager.material_start);
	mtl_destroy(&env->levels_manager.material_end);
	destroy_texture(&env->levels_manager.start);
	destroy_texture(&env->levels_manager.end);
}

void	free_levels_manager(t_env *env)
{
	SDL_FreeSurface(env->levels_manager.start_surface);
	SDL_FreeSurface(env->levels_manager.end_surface);
}
