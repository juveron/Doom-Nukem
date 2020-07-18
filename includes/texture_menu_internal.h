/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   texture_menu_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/06 16:42:59 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/29 18:28:00 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TEXTURE_MENU_INTERNAL_H
# define TEXTURE_MENU_INTERNAL_H

# include "doom_nukem.h"

bool	internal_texture_menu_5(t_container *container,
	t_material_menu *texture_menu, t_env *env);
bool	change_u_texture_scale(void *text, void *param);
bool	change_v_texture_scale(void *text, void *param);
bool	change_diffuse_color(void *text, void *param);
bool	change_u_texture_pos(void *text, void *param);
bool	change_v_texture_pos(void *text, void *param);
bool	change_texture_rotation(void *text, void *param);
bool	copy_material(void *param);
bool	past_material(void *param);

#endif
