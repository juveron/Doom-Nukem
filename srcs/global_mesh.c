/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_mesh.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:06:45 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 11:07:36 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void		free_global_mesh(t_env *env)
{
	destroy_texture(&env->skybox_texture);
	destroy_render_object(&env->skybox);
	destroy_mesh(&env->global_mesh.skybox_mesh);
	destroy_mesh(&env->global_mesh.cube_mesh);
	destroy_mesh(&env->global_mesh.fragment_mesh);
}

static bool	load_skybox(t_env *env)
{
	SDL_Surface *tex_tmp;
	SDL_Surface *tex_tmp2;

	mtl_destroy(&env->global_mesh.skybox_mesh->default_material);
	if (!(env->global_mesh.skybox_mesh->default_material = mtl_create()))
		return (false);
	env->global_mesh.skybox_mesh->default_material->
		use_advenced_movement = false;
	tex_tmp = import_tga("./assets/sky_rle.tga", false);
	tex_tmp2 = SDL_ConvertSurfaceFormat(tex_tmp, SDL_PIXELFORMAT_RGB888, 0);
	if (!tex_tmp2)
	{
		SDL_FreeSurface(tex_tmp);
		ft_dprintf(2, "Fail to load texture !\n");
		return (false);
	}
	env->skybox_texture = create_texture("skybox_texture", tex_tmp2, 0);
	SDL_FreeSurface(tex_tmp);
	if (!mtl_add_diffuse_texture(env->global_mesh.skybox_mesh->default_material,
		env->skybox_texture))
		return (false);
	env->skybox = create_render_object("Skybox", env->global_mesh.skybox_mesh,
		false, NULL);
	env->sky_enable = true;
	return (true);
}

bool		load_global_mesh(t_env *env)
{
	if (!(env->global_mesh.skybox_mesh = open_obj_file("./assets/skybox.obj",
			"skybox_mesh"))
		|| load_skybox(env) == false
		|| !(env->global_mesh.cube_mesh = open_obj_file(
			"./assets/cube_mesh.obj", "cube_mesh"))
		|| !(env->global_mesh.fragment_mesh = open_obj_file(
			"./assets/fragment.obj", "fragment_mesh")))
		return (false);
	return (true);
}
