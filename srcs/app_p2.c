/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   app_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 10:19:51 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/15 21:54:06 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static int	quit(void *data, SDL_Event *event)
{
	t_context	*context;

	(void)data;
	context = get_context();
	if (event->type == SDL_KEYDOWN)
	{
		if (event->key.keysym.scancode == SDL_SCANCODE_ESCAPE
			&& event->key.keysym.mod == KMOD_LCTRL)
			context->run = false;
	}
	return (1);
}

static bool	check_file_name(char *path)
{
	char	*name;

	if (ft_strequ(path, "--new") || ft_strequ(path, "-n"))
		return (true);
	if (!(name = get_file_name(path)))
		return (false);
	free(name);
	return (true);
}

bool		load_env_and_map(t_env **env, char **av)
{
	t_context	*context;

	if (!(context = get_context()))
		throw_error("DOOM_NUKEM: Fail to init context.", NULL);
	if (!check_file_name(av[1]))
		throw_error("DOOM_NUKEM: Wrong file.", NULL);
	*env = init_env();
	check_new_map_option(av[1], *env);
	if (!(*env)->test_mode)
	{
		if (!((*env)->map_file.file_name = get_file_name(av[1])))
			throw_error("DOOM_NUKEM: Fail to get file name.", *env);
		if (!import_maps(av[1], *env))
			throw_error("DOOM_NUKEM: Fail to load map !", *env);
		ft_printf("Success to load map\n");
	}
	SDL_AddEventWatch(&quit, *env);
	SDL_AddEventWatch(&input, *env);
	return (true);
}

void		free_all(t_env *env)
{
	free_global_mesh(env);
	destroy_custom_window(&env->gui.texture_window);
	destroy_custom_window(&env->gui.window);
	free_levels_manager(env);
	if (env->app_state == APP_EDITOR_GAME)
	{
		free_levels_manager_3d(env);
		free_remaining_objects(env);
		destroy_object_manager(env);
	}
	free_tiles_array();
	destroy_rasterizer_workers();
	free_all_scene(env);
	destroy_notify(env);
}
