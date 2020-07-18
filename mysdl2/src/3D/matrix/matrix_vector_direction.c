/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_vector_direction.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 11:26:20 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/30 11:43:11 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

/*
**	Use a matrix without scale for these function (transform.rot_pos)
*/

t_vec3f	matrix_vector_forward(t_matrix4 *matrix)
{
	return (vec3f(matrix->m[2][0], matrix->m[2][1], matrix->m[2][2]));
}

t_vec3f	matrix_vector_up(t_matrix4 *matrix)
{
	return (vec3f(matrix->m[1][0], matrix->m[1][1], matrix->m[1][2]));
}

t_vec3f	matrix_vector_left(t_matrix4 *matrix)
{
	return (vec3f(matrix->m[0][0], matrix->m[0][1], matrix->m[0][2]));
}
