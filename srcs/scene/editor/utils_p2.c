/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_p2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/01 14:37:10 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/01 14:37:11 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

void	free_tmp_vertices(t_env *env)
{
	t_point	**point;
	size_t	i;

	point = env->editor.tmp_vertices.items;
	i = 0;
	while (i < env->editor.tmp_vertices.total)
	{
		point_free(point[i]);
		i++;
	}
	vector_free(&env->editor.tmp_vertices);
}

void	free_tmp_sector(t_env *env)
{
	free_sector(env->editor.tmp_sector);
}

bool	is_over_gui_window(t_env *env)
{
	if (!env->gui.window->component.is_visible
		&& !env->gui.texture_menu->window->component.is_visible)
		return (0);
	return (env->gui.window->is_over || env->gui.texture_menu->window->is_over);
}
