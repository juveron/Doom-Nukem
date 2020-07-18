/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_scale.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 16:16:05 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/28 11:09:44 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

void	matrix_scale(float x, float y, float z, t_matrix4 *out)
{
	matrix_identity(out);
	if (x != 0)
		out->m[0][0] = x;
	if (y != 0)
		out->m[1][1] = y;
	if (z != 0)
		out->m[2][2] = z;
}
