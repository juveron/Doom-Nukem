/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_dot.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:25:26 by kguibout          #+#    #+#             */
/*   Updated: 2019/08/14 11:04:40 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

float	vec2i_dot(t_vec2i vec1, t_vec2i vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

float	vec2f_dot(t_vec2f vec1, t_vec2f vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

float	vec2d_dot(t_vec2d vec1, t_vec2d vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}

float	vec2ui_dot(t_vec2ui vec1, t_vec2ui vec2)
{
	return (vec1.x * vec2.x + vec1.y * vec2.y);
}
