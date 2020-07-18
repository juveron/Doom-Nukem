/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   internal_handler.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:50:05 by thboura           #+#    #+#             */
/*   Updated: 2020/06/20 16:51:24 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef INTERNAL_HANDLER_H
# define INTERNAL_HANDLER_H

# include "doom_nukem.h"

typedef struct	s_farthest_handler
{
	float	distance;
	float	d;
	t_u32	return_value;
}				t_farthest_handler;

typedef struct	s_collision_handler
{
	t_sector			*sector;
	t_triangle			*triangle;
	t_triangle			*triangle2;
	t_capsule_collider	capsule;
	t_vec3f				look_dir;
	t_matrix4			m_rot;
	t_vec3f				col;
	t_vec3f				new_pos;
	t_vec3f				old_pos;
	bool				in;
}				t_collision_handler;

typedef struct	s_add_level_handler
{
	t_vec3f			*position;
	bool			is_start;
	t_level_point	new_pos;
	bool			ret;
}				t_add_level_handler;

#endif
