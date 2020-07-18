/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/12 10:57:35 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/13 02:00:54 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "game.h"
#include "inputs.h"

static bool		set_pvs_sector(t_env *env, t_sector *sector)
{
	t_game		*game;
	size_t		i;
	t_unique_id	*id;

	game = env->game;
	game->current_sector = sector;
	vector_free(&game->visible_sector);
	vector_init(&game->visible_sector, sizeof(t_sector *));
	i = 0;
	id = sector->pvs.sector.items;
	while (i < sector->pvs.sector.total)
	{
		if (!vector_push(&game->visible_sector, map_get(
			env->current_map->sectors, id[i])))
			return (false);
		++i;
	}
	return (vector_push(&game->visible_sector, &sector));
}

static t_sector	*get_current_sector(t_env *env, t_vec2f *vec)
{
	t_sector	*sector;

	sector = is_in_sector(env, vec, true);
	if (sector == NULL)
	{
		env->player.transform->position = env->current_map->
			level.start.position;
		if (!(sector = is_in_sector(env, vec, true)))
			return (NULL);
	}
	return (sector);
}

static bool		updates_in_game(t_env *env)
{
	if (!update_input(env)
		|| !update_game_pause(env, &env->gui.game_pause_menu)
		|| !update_level(env, env->ph_context.dt))
		return (false);
	update_pickup_object(env);
	return (true);
}

static bool		update_game_sector(t_env *env)
{
	t_sector	*sector;
	t_vec2f		vec;

	vec.x = env->player.transform->position.x;
	vec.y = env->player.transform->position.z;
	if (!(sector = get_current_sector(env, &vec)))
		return (false);
	if (sector != env->game->current_sector)
	{
		if (!set_pvs_sector(env, sector))
			return (false);
	}
	return (true);
}

bool			update_game(void *param)
{
	t_env		*env;

	env = param;
	env->player.state = 0;
	if (env->gui.status == GUI_NONE)
	{
		if (!set_listener_position(env->player.transform->position)
			|| !set_listener_orientation(camera_forward(&env->camera),
				camera_up(&env->camera)))
			return (false);
		if (!ph_loop(&env->ph_context))
			return (false);
	}
	if (!updates_in_game(env))
		return (false);
	return (update_game_sector(env));
}
