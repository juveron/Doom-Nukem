/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   win_menu_function.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 16:31:01 by thboura           #+#    #+#             */
/*   Updated: 2020/07/15 03:07:28 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	set_highscore(t_env *env)
{
	const char	*tmp_str;
	char		buffer[32];
	t_u64		tmp_score;

	tmp_str = "";
	tmp_score = clock_get_milliseconds(&env->hud.time);
	if (env->game->highscore == 0 || env->game->highscore > tmp_score)
	{
		env->game->highscore = tmp_score;
		tmp_str = "New ";
	}
	ft_snprintf(buffer, sizeof(buffer), "%sHighscore: %02lu:%02lu:%02lu",
		tmp_str, env->game->highscore / 1000 / 60 % 60,
		env->game->highscore / 1000 % 60, env->game->highscore % 1000 / 10);
	if (!label_change_name(env->gui.win_menu.highscore_label, buffer))
		return (false);
	env->gui.win_menu.highscore_label->component.rect.x = env->main_window->
		size.x / 2 - env->gui.win_menu.highscore_label->component.rect.w / 2;
	env->gui.win_menu.highscore_label->component.rect.y = env->gui.win_menu.
		time_label->component.rect.y + env->gui.win_menu.time_label->
		component.rect.h;
	return (true);
}

bool	resume_win_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->gui.status = GUI_NONE;
	env->gui.win_menu.container->component.is_visible = false;
	env->main_window->main_container->component.need_redraw = true;
	env->current_map = *(t_doom_map **)vector_get(&env->maps, 0);
	env->current_map_index = 0;
	env->game->current_segment_time = 0;
	if (!set_game_start(env))
		return (false);
	env->gui.win_menu.container->component.use_background = false;
	env->gui.win_menu.win_label->component.use_background = false;
	env->gui.win_menu.animation = true;
	env->gui.win_menu.current_time = 0;
	return (true);
}

bool	main_menu_win_menu(void *param)
{
	t_env	*env;

	env = (t_env *)param;
	env->time_scale = 1.f;
	load_scene(env->scenes.main_menu);
	return (true);
}

bool	exit_win_menu(void *param)
{
	(void)param;
	get_context()->run = false;
	return (true);
}
