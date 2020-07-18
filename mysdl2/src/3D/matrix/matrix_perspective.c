/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_perspective.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:22:25 by kguibout          #+#    #+#             */
/*   Updated: 2020/02/12 08:21:30 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"
#include <math.h>

float		to_radian(float degre)
{
	return (degre * (M_PI / 180));
}

t_matrix4	matrix_perspective_fov(float fov, float aspect_ratio,
	float z_near, float z_far)
{
	t_matrix4	out;
	const float tan_half_fov = tanf(to_radian(fov / 2.f));
	const float z_range = z_near - z_far;

	out.m[0][0] = 1.f / (tan_half_fov * aspect_ratio);
	out.m[0][1] = 0;
	out.m[0][2] = 0;
	out.m[0][3] = 0;
	out.m[1][0] = 0;
	out.m[1][1] = 1.f / tan_half_fov;
	out.m[1][2] = 0;
	out.m[1][3] = 0;
	out.m[2][0] = 0;
	out.m[2][1] = 0;
	out.m[2][2] = (-z_near - z_far) / z_range;
	out.m[2][3] = 2.f * z_far * z_near / z_range;
	out.m[3][0] = 0;
	out.m[3][1] = 0;
	out.m[3][2] = 1;
	out.m[3][3] = 0;
	return (out);
}
