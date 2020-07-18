/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invert_internal.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/07 17:59:20 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/08 12:33:39 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

/*
**	These functions are not optimized/readable due to the 42 Norm ...
*/

static void	swap_double(double *a, double *b)
{
	double	c;

	c = *a;
	*a = *b;
	*b = c;
}

bool		swap_row(size_t column, t_matrix4 *in, t_matrix4 *out)
{
	size_t	row;
	size_t	big;
	size_t	j;

	big = column;
	row = 0;
	while (row < 4)
	{
		if (fabs(in->m[row++][column]) > fabs(in->m[big][column]))
			big = row - 1;
	}
	if (big == column)
	{
		ft_dprintf(2, "Unable to invert singular matrix !\n");
		matrix_identity(out);
		return (0);
	}
	j = 0;
	while (j < 4)
	{
		swap_double(&in->m[column][j], &in->m[big][j]);
		swap_double(&out->m[column][j], &out->m[big][j]);
		j++;
	}
	return (1);
}

void		set_each_row_to_zero(size_t column, t_matrix4 *in,
	t_matrix4 *out)
{
	size_t	row;
	size_t	j;
	double	coef;

	row = 0;
	while (row < 4)
	{
		if (row != column)
		{
			coef = in->m[row][column] / in->m[column][column];
			if (coef != 0)
			{
				j = 0;
				while (j < 4)
				{
					in->m[row][j] -= coef * in->m[column][j];
					out->m[row][j] -= coef * out->m[column][j];
					j++;
				}
				in->m[row][column] = 0;
			}
		}
		row++;
	}
}

void		scale_element_to_1(t_matrix4 *in, t_matrix4 *out)
{
	size_t		column;
	size_t		row;

	row = 0;
	while (row < 4)
	{
		column = 0;
		while (column < 4)
		{
			out->m[row][column] /= in->m[row][row];
			column++;
		}
		row++;
	}
}

void		set_zero_value(t_matrix4 *matrix)
{
	size_t	i;
	size_t	j;

	i = 0;
	while (i < 4)
	{
		j = 0;
		while (j < 4)
		{
			if (fabs(matrix->m[i][j]) < 0.0000001f)
				matrix->m[i][j] = 0;
			++j;
		}
		++i;
	}
}
