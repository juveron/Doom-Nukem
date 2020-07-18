/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_editor_internal.h                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/04 17:42:34 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/05 10:48:54 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DRAW_EDITOR_INTERNAL_H
# define DRAW_EDITOR_INTERNAL_H

# include "doom_nukem.h"
# include "editor.h"

void	process_vertex_wall(t_env *env, t_sector *sector);
bool	draw_3d_mode(t_env *env);
bool	draw_editor(void *param);
bool	update_editor(void *param);

#endif
