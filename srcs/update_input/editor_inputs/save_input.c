/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_input.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/28 09:52:00 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 14:31:44 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "inputs.h"

static void	map_message(t_env *env, char *pathfile)
{
	char	tmp_buff[45];

	ft_snprintf(tmp_buff, sizeof(tmp_buff), "Map saved to %s", pathfile);
	send_notify(tmp_buff, 0XFFFFFF, env);
}

bool		save_map_input(t_env *env)
{
	char	buff[32];

	if (get_key(SDL_SCANCODE_LCTRL)
		&& get_key_down(env->shortcuts.editor.major.save))
	{
		if (env->map_file.file_name == NULL)
			ft_strlcpy(buff, "default_name.dmap", sizeof(buff));
		else
			ft_snprintf(buff, sizeof(buff), "%s.dmap", env->map_file.file_name);
		if (!export_map_file(buff, env))
		{
			send_notify("Failed to save map", 0xFF0000, env);
			return (false);
		}
		map_message(env, buff);
	}
	return (true);
}
