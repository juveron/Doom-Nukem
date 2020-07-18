/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_options_p2.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:35:55 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 16:06:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	create_controls_options_p6(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->move_up_button = create_input_button((SDL_Rect){
			button_template.x, 4 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->move_up_button,
			get_used_key_string(env->shortcuts.game.user.move_up))
		|| !add_custom_action(controls->move_up_button->on_click,
			&(t_custom_event){&init_input_event, &change_move_up_key})
		|| !container_add(controls->container, controls->move_up_button))
		return (destroy_controls_options(controls));
	if (!(controls->move_down_label = create_label(vec2i(25,
			5 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->move_down_label, "Down")
		|| !container_add(controls->container, controls->move_down_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p7(env, controls, button_template));
}

static bool	create_controls_options_p5(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->move_right_button = create_input_button((SDL_Rect){
			button_template.x, 3 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->move_right_button,
			get_used_key_string(env->shortcuts.game.user.move_right))
		|| !add_custom_action(controls->move_right_button->on_click,
			&(t_custom_event){&init_input_event, &change_move_right_key})
		|| !container_add(controls->container, controls->move_right_button))
		return (destroy_controls_options(controls));
	if (!(controls->move_up_label = create_label(vec2i(25,
			4 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->move_up_label, "Up")
		|| !container_add(controls->container, controls->move_up_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p6(env, controls, button_template));
}

static bool	create_controls_options_p4(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->move_left_button = create_input_button((SDL_Rect){
			button_template.x, 2 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->move_left_button,
			get_used_key_string(env->shortcuts.game.user.move_left))
		|| !add_custom_action(controls->move_left_button->on_click,
			&(t_custom_event){&init_input_event, &change_move_left_key})
		|| !container_add(controls->container, controls->move_left_button))
		return (destroy_controls_options(controls));
	if (!(controls->move_right_label = create_label(vec2i(25,
			3 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->move_right_label, "Right")
		|| !container_add(controls->container, controls->move_right_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p5(env, controls, button_template));
}

static bool	create_controls_options_p3(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->move_back_button = create_input_button((SDL_Rect){
			button_template.x, 1 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->move_back_button,
			get_used_key_string(env->shortcuts.game.user.move_back))
		|| !add_custom_action(controls->move_back_button->on_click,
			&(t_custom_event){&init_input_event, &change_move_back_key})
		|| !container_add(controls->container, controls->move_back_button))
		return (destroy_controls_options(controls));
	if (!(controls->move_left_label = create_label(vec2i(25,
			2 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->move_left_label, "Left")
		|| !container_add(controls->container, controls->move_left_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p4(env, controls, button_template));
}

bool		create_controls_options_p2(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->move_forward_button = create_input_button((SDL_Rect){
			button_template.x, 0 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->move_forward_button,
			get_used_key_string(env->shortcuts.game.user.move_forward))
		|| !add_custom_action(controls->move_forward_button->on_click,
			&(t_custom_event){&init_input_event, &change_move_forward_key})
		|| !container_add(controls->container, controls->move_forward_button))
		return (destroy_controls_options(controls));
	if (!(controls->move_back_label = create_label(vec2i(25,
			1 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->move_back_label, "Back")
		|| !container_add(controls->container, controls->move_back_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p3(env, controls, button_template));
}
