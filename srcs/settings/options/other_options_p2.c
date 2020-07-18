/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   other_options_p2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/27 12:59:12 by thboura           #+#    #+#             */
/*   Updated: 2020/06/27 13:01:28 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	create_other_options_p4(t_env *env, t_other_options *other,
	SDL_Rect option_template)
{
	if (!(other->game_over_animation_label = create_label(vec2i(25,
			3 * option_template.h + option_template.y + (option_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(other->game_over_animation_label,
			"Game over animation")
		|| !container_add(other->container, other->game_over_animation_label))
		return (destroy_other_options(other));
	if (!(other->game_over_animation_check_box = create_check_box((SDL_Rect){
			option_template.x, 3 * option_template.h + option_template.y
			+ (option_template.h / 2 - 25), 50, 50}, 0x000000FF))
		|| !add_custom_action(other->game_over_animation_check_box->on_toggle,
			&(t_custom_event){&enable_animation, env})
		|| !container_add(other->container,
			other->game_over_animation_check_box))
		return (destroy_other_options(other));
	if (!container_add(env->gui.settings_menu.container, other->container))
		return (destroy_other_options(other));
	other->container->component.is_visible = false;
	return (true);
}

static bool	create_other_options_p3(t_env *env, t_other_options *other,
	SDL_Rect option_template)
{
	if (!(other->fps_label = create_label(vec2i(25,
			2 * option_template.h + option_template.y + (option_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(other->fps_label, "Fps")
		|| !container_add(other->container, other->fps_label))
		return (destroy_other_options(other));
	if (!(other->fps_check_box = create_check_box((SDL_Rect){
			option_template.x, 2 * option_template.h + option_template.y
			+ (option_template.h / 2 - 25), 50, 50}, 0x000000FF))
		|| !add_custom_action(other->fps_check_box->on_toggle,
			&(t_custom_event){&enable_fps, env})
		|| !container_add(other->container, other->fps_check_box))
		return (destroy_other_options(other));
	return (create_other_options_p4(env, other, option_template));
}

bool		create_other_options_p2(t_env *env, t_other_options *other,
	SDL_Rect option_template)
{
	if (!(other->skybox_check_box = create_check_box((SDL_Rect){
			option_template.x, 0 * option_template.h + option_template.y
			+ (option_template.h / 2 - 25), 50, 50}, 0x000000FF))
		|| !add_custom_action(other->skybox_check_box->on_toggle,
			&(t_custom_event){&disable_skybox, env})
		|| !container_add(other->container, other->skybox_check_box))
		return (destroy_other_options(other));
	if (!(other->debug_triangles_label = create_label(vec2i(25,
			1 * option_template.h + option_template.y + (option_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(other->debug_triangles_label, "Debug triangles")
		|| !container_add(other->container, other->debug_triangles_label))
		return (destroy_other_options(other));
	if (!(other->debug_triangles_check_box = create_check_box((SDL_Rect){
			option_template.x, 1 * option_template.h + option_template.y
			+ (option_template.h / 2 - 25), 50, 50}, 0x000000FF))
		|| !add_custom_action(other->debug_triangles_check_box->on_toggle,
			&(t_custom_event){&enable_debug_triangles, env})
		|| !container_add(other->container, other->debug_triangles_check_box))
		return (destroy_other_options(other));
	return (create_other_options_p3(env, other, option_template));
}
