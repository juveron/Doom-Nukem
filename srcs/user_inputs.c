/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   user_inputs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:19:59 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 16:10:40 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	is_scancode_user_input(t_user_inputs *user_inputs,
	SDL_Scancode scancode)
{
	return (scancode == user_inputs->move_forward
		|| scancode == user_inputs->move_back
		|| scancode == user_inputs->move_left
		|| scancode == user_inputs->move_right
		|| scancode == user_inputs->move_up
		|| scancode == user_inputs->move_down
		|| scancode == user_inputs->jump
		|| scancode == user_inputs->sprint
		|| scancode == user_inputs->crouch);
}

void	set_default_user_inputs(t_user_inputs *user_inputs)
{
	user_inputs->move_forward = SDL_SCANCODE_W;
	user_inputs->move_back = SDL_SCANCODE_S;
	user_inputs->move_left = SDL_SCANCODE_A;
	user_inputs->move_right = SDL_SCANCODE_D;
	user_inputs->move_up = SDL_SCANCODE_Q;
	user_inputs->move_down = SDL_SCANCODE_E;
	user_inputs->jump = SDL_SCANCODE_SPACE;
	user_inputs->sprint = SDL_SCANCODE_LSHIFT;
	user_inputs->crouch = SDL_SCANCODE_LCTRL;
}
