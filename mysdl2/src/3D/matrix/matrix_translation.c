/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_translation.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 14:35:10 by kguibout          #+#    #+#             */
/*   Updated: 2019/11/25 11:29:06 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

void	matrix_translation(float x, float y, float z, t_matrix4 *out)
{
	matrix_identity(out);
	out->m[3][0] = x;
	out->m[3][1] = y;
	out->m[3][2] = z;
}
