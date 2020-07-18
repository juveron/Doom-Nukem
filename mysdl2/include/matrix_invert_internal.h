/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_invert_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 12:34:46 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 12:34:47 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATRIX_INVERT_INTERNAL_H
# define MATRIX_INVERT_INTERNAL_H

# include "draw3d.h"

void	set_zero_value(t_matrix4 *matrix);
bool	swap_row(size_t column, t_matrix4 *in, t_matrix4 *out);
void	set_each_row_to_zero(size_t column, t_matrix4 *in,
			t_matrix4 *out);
void	scale_element_to_1(t_matrix4 *in, t_matrix4 *out);

#endif
