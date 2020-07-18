/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_main_menu_inputs.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/19 16:59:11 by thboura           #+#    #+#             */
/*   Updated: 2020/06/19 17:12:28 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	global_main_menu_inputs(t_env *env)
{
	if (get_key_down(env->shortcuts.menu.quit))
		get_context()->run = false;
	return (true);
}
