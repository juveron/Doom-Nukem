/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   history_input.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/24 11:54:47 by thboura           #+#    #+#             */
/*   Updated: 2020/06/24 12:03:29 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

bool	set_history(t_env *env, t_history_window *history)
{
	if (get_key_down(env->shortcuts.editor.history))
	{
		if (!history->available)
		{
			if (!init_history(env, history))
				return (false);
		}
		else
			destroy_history(history);
	}
	return (true);
}
