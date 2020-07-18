/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_rotation.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:05:36 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 22:13:43 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"
#include <math.h>

void	matrix_rotation_x(float rad, t_matrix4 *out)
{
	matrix_identity(out);
	out->m[1][1] = cos(rad);
	out->m[2][1] = -sin(rad);
	out->m[1][2] = sin(rad);
	out->m[2][2] = cos(rad);
}

void	matrix_rotation_y(float rad, t_matrix4 *out)
{
	matrix_identity(out);
	out->m[0][0] = cos(rad);
	out->m[0][2] = sin(rad);
	out->m[2][0] = -sin(rad);
	out->m[2][2] = cos(rad);
}

void	matrix_rotation_z(float rad, t_matrix4 *out)
{
	matrix_identity(out);
	out->m[0][0] = cos(rad);
	out->m[1][0] = -sin(rad);
	out->m[0][1] = sin(rad);
	out->m[1][1] = cos(rad);
}

void	matrix_rotation(float x, float y, float z, t_matrix4 *out)
{
	float		rad;
	t_matrix4	tmp;

	matrix_identity(out);
	if (y != 0)
	{
		rad = radian(y);
		matrix_rotation_y(rad, out);
	}
	if (x != 0)
	{
		rad = radian(x);
		matrix_rotation_x(rad, &tmp);
		*out = matrix_multiply(&tmp, out);
	}
	if (z != 0)
	{
		rad = radian(z);
		matrix_rotation_z(rad, &tmp);
		*out = matrix_multiply(&tmp, out);
	}
}
