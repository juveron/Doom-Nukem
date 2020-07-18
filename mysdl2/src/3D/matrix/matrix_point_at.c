/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_point_at.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/17 15:57:58 by kguibout          #+#    #+#             */
/*   Updated: 2019/11/18 09:10:08 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

void	matrix_point_at(t_vec3f *pos, t_vec3f *target, t_vec3f *up)
{
	t_vec3f		new_forward;
	t_vec3f		a;
	t_vec3f		new_up;
	t_vec3f		new_right;
	t_matrix4	m_out;

	new_forward = vec3f_normalize(vec3f_sub(*target, *pos));
	a = vec3f_mul(new_forward, vec3f_dot(*up, new_forward));
	new_up = vec3f_normalize(vec3f_sub(*up, a));
	new_right = vec3f_cross(new_up, new_forward);
	matrix_identity(&m_out);
	m_out.m[0][0] = new_right.x;
	m_out.m[0][1] = new_right.y;
	m_out.m[0][2] = new_right.z;
	m_out.m[1][0] = new_up.x;
	m_out.m[1][1] = new_up.y;
	m_out.m[1][2] = new_up.z;
	m_out.m[2][0] = new_forward.x;
	m_out.m[2][1] = new_forward.y;
	m_out.m[2][2] = new_forward.z;
	m_out.m[3][0] = pos->x;
	m_out.m[3][1] = pos->y;
	m_out.m[3][2] = pos->z;
	return (m_out);
}
