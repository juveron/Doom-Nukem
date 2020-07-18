/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_multiply.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 15:25:55 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/17 11:30:17 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

t_matrix4	matrix_multiply(t_matrix4 *in1, t_matrix4 *in2)
{
	size_t		i;
	size_t		j;
	t_matrix4	out;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out.m[i][j] = in1->m[i][0] * in2->m[0][j] + in1->m[i][1]
				* in2->m[1][j] + in1->m[i][2] * in2->m[2][j] + in1->m[i][3]
				* in2->m[3][j];
			j++;
		}
		i++;
	}
	return (out);
}

void		matrix_multiply2(t_matrix4 *in1, t_matrix4 *in2, t_matrix4 *out)
{
	size_t		i;
	size_t		j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			out->m[i][j] = in1->m[i][0] * in2->m[0][j] + in1->m[i][1]
				* in2->m[1][j] + in1->m[i][2] * in2->m[2][j] + in1->m[i][3]
				* in2->m[3][j];
			j++;
		}
		i++;
	}
}
