/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   global_settings_inputs.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/23 17:50:12 by thboura           #+#    #+#             */
/*   Updated: 2020/04/15 18:00:53 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	global_settings_inputs(t_env *env)
{
	if (get_key_down(env->shortcuts.menu.quit))
		resume_settings_menu(env);
	return (true);
}
