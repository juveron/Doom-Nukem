/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invert.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/26 17:14:07 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/31 21:28:47 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "matrix_invert_internal.h"

/*
**	These functions are not optimized/readable due to the 42 Norm ...
*/

t_matrix4	matrix_invert(t_matrix4 *in)
{
	size_t		column;
	t_matrix4	out;

	matrix_identity(&out);
	set_zero_value(in);
	column = 0;
	while (column < 4)
	{
		if (in->m[column][column] == 0.f)
			if (swap_row(column, in, &out) == 0)
				return (out);
		set_each_row_to_zero(column, in, &out);
		column++;
	}
	scale_element_to_1(in, &out);
	return (out);
}

t_matrix4	matrix_invert2(t_matrix4 in)
{
	size_t		column;
	t_matrix4	out;

	matrix_identity(&out);
	set_zero_value(&in);
	column = 0;
	while (column < 4)
	{
		if (in.m[column][column] == 0.f)
			if (swap_row(column, &in, &out) == 0)
				return (out);
		set_each_row_to_zero(column, &in, &out);
		column++;
	}
	scale_element_to_1(&in, &out);
	return (out);
}
