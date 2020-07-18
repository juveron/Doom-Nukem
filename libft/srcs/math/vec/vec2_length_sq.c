/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_length_sq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:46:07 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/14 12:52:17 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	vec2i_length_sq(t_vec2i vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y);
}

float	vec2f_length_sq(t_vec2f vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y);
}

float	vec2d_length_sq(t_vec2d vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y);
}

float	vec2ui_length_sq(t_vec2ui vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y);
}
