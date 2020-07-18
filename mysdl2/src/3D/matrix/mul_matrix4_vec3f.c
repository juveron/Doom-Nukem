/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mul_matrix4_vec3f.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 14:58:25 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/11 08:34:25 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

void	mul_matrix4_vec3f(t_vec3f *i, t_vec3f *o, t_matrix4 *mat)
{
	float	w;

	o->x = i->x * mat->m[0][0] + i->y * mat->m[1][0] + i->z * mat->m[2][0]
		+ mat->m[3][0];
	o->y = i->x * mat->m[0][1] + i->y * mat->m[1][1] + i->z * mat->m[2][1]
		+ mat->m[3][1];
	o->z = i->x * mat->m[0][2] + i->y * mat->m[1][2] + i->z * mat->m[2][2]
		+ mat->m[3][2];
	w = i->x * mat->m[0][3] + i->y * mat->m[1][3] + i->z * mat->m[2][3]
		+ mat->m[3][3];
	if (w != 0.f)
	{
		o->x /= w;
		o->y /= w;
		o->z /= w;
	}
}