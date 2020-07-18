/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_options_p3.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:36:14 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 16:06:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

static bool	create_controls_options_p10(t_env *env,
	t_controls_options *controls, SDL_Rect button_template)
{
	(void)button_template;
	if (!(controls->crouch_button = create_input_button((SDL_Rect){
			button_template.x, 8 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->crouch_button,
			get_used_key_string(env->shortcuts.game.user.crouch))
		|| !add_custom_action(controls->crouch_button->on_click,
			&(t_custom_event){&init_input_event, &change_crouch_key})
		|| !container_add(controls->container, controls->crouch_button))
		return (destroy_controls_options(controls));
	if (!container_add(env->gui.settings_menu.container, controls->container))
		return (destroy_controls_options(controls));
	controls->container->component.is_visible = false;
	return (true);
}

static bool	create_controls_options_p9(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->sprint_button = create_input_button((SDL_Rect){
			button_template.x, 7 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->sprint_button,
			get_used_key_string(env->shortcuts.game.user.sprint))
		|| !add_custom_action(controls->sprint_button->on_click,
			&(t_custom_event){&init_input_event, &change_sprint_key})
		|| !container_add(controls->container, controls->sprint_button))
		return (destroy_controls_options(controls));
	if (!(controls->crouch_label = create_label(vec2i(25,
			8 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->crouch_label, "Crouch")
		|| !container_add(controls->container, controls->crouch_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p10(env, controls, button_template));
}

static bool	create_controls_options_p8(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->jump_button = create_input_button((SDL_Rect){
			button_template.x, 6 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->jump_button,
			get_used_key_string(env->shortcuts.game.user.jump))
		|| !add_custom_action(controls->jump_button->on_click,
			&(t_custom_event){&init_input_event, &change_jump_key})
		|| !container_add(controls->container, controls->jump_button))
		return (destroy_controls_options(controls));
	if (!(controls->sprint_label = create_label(vec2i(25,
			7 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->sprint_label, "Sprint")
		|| !container_add(controls->container, controls->sprint_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p9(env, controls, button_template));
}

bool		create_controls_options_p7(t_env *env, t_controls_options *controls,
	SDL_Rect button_template)
{
	if (!(controls->move_down_button = create_input_button((SDL_Rect){
			button_template.x, 5 * button_template.h + button_template.y,
			button_template.w, button_template.h}, 0x333333FF,
			env->fonts.deja_vu_sans_momo_16, env))
		|| !input_button_change_name(controls->move_down_button,
			get_used_key_string(env->shortcuts.game.user.move_down))
		|| !add_custom_action(controls->move_down_button->on_click,
			&(t_custom_event){&init_input_event, &change_move_down_key})
		|| !container_add(controls->container, controls->move_down_button))
		return (destroy_controls_options(controls));
	if (!(controls->jump_label = create_label(vec2i(25,
			6 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->jump_label, "Jump")
		|| !container_add(controls->container, controls->jump_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p8(env, controls, button_template));
}
