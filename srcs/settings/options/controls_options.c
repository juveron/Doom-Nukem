/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   controls_options.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 18:34:37 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 12:00:12 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

const char	*get_used_key_string(SDL_Scancode scancode)
{
	static const char	*basic_keys[66] = {"A", "B", "C", "D", "E", "F", "G",
		"H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U",
		"V", "W", "X", "Y", "Z", "1", "2", "3", "4", "5", "6", "7", "8", "9",
		"0", "RETURN", "ESCAPE", "BACKSPACE", "TAB", "SPACE", "MINUS", "EQUALS",
		"LEFT_BRACKET", "RIGHT_BRACKET", "BACKSLASH", "NONUSHASH", "SEMICOLON",
		"APOSTROPHE", "GRAVE", "COMMA", "PERIOD", "SLASH"};
	static const char	*extra_keys[20] = {"RIGHT", "LEFT", "DOWN", "UP",
		"NUM_LOCKCLEAR", "KP_DIVIDE", "KP_MULTIPLY", "KP_MINUS", "KP_PLUS",
		"KP_ENTER", "KP_1", "KP_2", "KP_3", "KP_4", "KP_5", "KP_6", "KP_7",
		"KP_8", "KP_9", "KP_0"};

	if (scancode == SDL_SCANCODE_LCTRL)
		return ((const char *)"CTRL (LEFT)");
	if (scancode == SDL_SCANCODE_LSHIFT)
		return ((const char *)"SHIFT (LEFT)");
	if (scancode < SDL_SCANCODE_A || (scancode > SDL_SCANCODE_SLASH
		&& scancode < SDL_SCANCODE_RIGHT) || scancode > SDL_SCANCODE_KP_0
		|| scancode == SDL_SCANCODE_NUMLOCKCLEAR
		|| scancode == SDL_SCANCODE_ESCAPE)
		return (NULL);
	if (scancode <= SDL_SCANCODE_SLASH)
		return (basic_keys[scancode - SDL_SCANCODE_A]);
	else
		return (extra_keys[scancode - SDL_SCANCODE_RIGHT]);
}

bool		reset_control_key(t_env *env, t_gui_input_button *button,
	SDL_Scancode *key_address, SDL_Scancode new_scancode)
{
	const char	*used_key_string;

	if (new_scancode == 0)
		return (true);
	if (is_input_game_shortcut(&env->shortcuts.game, new_scancode)
		|| is_scancode_user_input(&env->shortcuts.game.user, new_scancode))
	{
		ft_printf("This input is already used\n");
		return (true);
	}
	if (!(used_key_string = get_used_key_string(new_scancode)))
	{
		ft_printf("This input can't be used as control key\n");
		return (true);
	}
	*key_address = new_scancode;
	return (input_button_change_name(button, used_key_string));
}

bool		destroy_controls_options(t_controls_options *controls)
{
	int ret;

	ret = 0;
	if (!controls)
		return (false);
	ret += !destroy_input_button(&controls->jump_button);
	ret += !destroy_label(&controls->jump_label);
	ret += !destroy_input_button(&controls->move_down_button);
	ret += !destroy_label(&controls->move_down_label);
	ret += !destroy_input_button(&controls->move_up_button);
	ret += !destroy_label(&controls->move_up_label);
	ret += !destroy_input_button(&controls->move_right_button);
	ret += !destroy_label(&controls->move_right_label);
	ret += !destroy_input_button(&controls->move_left_button);
	ret += !destroy_label(&controls->move_left_label);
	ret += !destroy_input_button(&controls->move_back_button);
	ret += !destroy_label(&controls->move_back_label);
	ret += !destroy_input_button(&controls->move_forward_button);
	ret += !destroy_label(&controls->move_forward_label);
	ret += !destroy_input_button(&controls->sprint_button);
	ret += !destroy_label(&controls->sprint_label);
	ret += !destroy_input_button(&controls->crouch_button);
	ret += !destroy_label(&controls->crouch_label);
	ret += !destroy_container(&controls->container);
	return (ret == 0);
}

bool		create_controls_options(t_env *env, t_controls_options *controls)
{
	SDL_Rect	button_template;
	size_t		num_of_controls;

	num_of_controls = 9;
	button_template.w = env->main_window->size.x / 5;
	button_template.h = (env->main_window->size.y - 50) / num_of_controls;
	button_template.x = env->main_window->size.x - (button_template.w + 100);
	button_template.y = (env->main_window->size.y - 50) % num_of_controls;
	if (!(controls->container = create_container((SDL_Rect){0, 50,
		env->main_window->size.x, env->main_window->size.y - 50}, true,
		0X777777FF)))
		return (false);
	if (!(controls->move_forward_label = create_label(vec2i(25,
			0 * button_template.h + button_template.y + (button_template.h - 19)
			/ 2), 0xFFFFFFFF, env->fonts.deja_vu_sans_momo_16, 0x333333FF))
		|| !label_change_name(controls->move_forward_label, "Forward")
		|| !container_add(controls->container, controls->move_forward_label))
		return (destroy_controls_options(controls));
	return (create_controls_options_p2(env, controls, button_template));
}

bool		init_controls_options(void *param)
{
	t_env	*env;

	env = param;
	if (env->gui.settings_menu.current_option != CONTROLS_OPTION)
	{
		env->gui.settings_menu.controls_button->component.
			background = 0X777777FF;
		env->gui.settings_menu.controls_button->component.need_redraw = true;
		disable_current_option(&env->gui.settings_menu);
	}
	env->gui.settings_menu.current_option = CONTROLS_OPTION;
	env->gui.settings_menu.controls.container->component.is_visible = true;
	return (true);
}
