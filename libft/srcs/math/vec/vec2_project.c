/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2_project.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 10:57:13 by kguibout          #+#    #+#             */
/*   Updated: 2019/09/30 10:56:14 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

t_vec2i		vec2i_project(t_vec2i vec1, t_vec2i vec2)
{
	float	den;
	float	dp;
	float	mul;

	den = vec2i_dot(vec2, vec2);
	if (den != 0)
	{
		dp = vec2i_dot(vec1, vec2);
		mul = dp / den;
		return ((t_vec2i){vec2.x * mul, vec2.y * mul});
	}
	return ((t_vec2i){0, 0});
}

t_vec2f		vec2f_project(t_vec2f vec1, t_vec2f vec2)
{
	float	den;
	float	dp;
	float	mul;

	den = vec2f_dot(vec2, vec2);
	if (den != 0)
	{
		dp = vec2f_dot(vec1, vec2);
		mul = dp / den;
		return ((t_vec2f){vec2.x * mul, vec2.y * mul});
	}
	return ((t_vec2f){0, 0});
}

t_vec2d		vec2d_project(t_vec2d vec1, t_vec2d vec2)
{
	float	den;
	float	dp;
	float	mul;

	den = vec2d_dot(vec2, vec2);
	if (den != 0)
	{
		dp = vec2d_dot(vec1, vec2);
		mul = dp / den;
		return (vec2d(vec2.x * mul, vec2.y * mul));
	}
	return (vec2d(0, 0));
}

t_vec2ui	vec2ui_project(t_vec2ui vec1, t_vec2ui vec2)
{
	float	den;
	float	dp;
	float	mul;

	den = vec2ui_dot(vec2, vec2);
	if (den != 0)
	{
		dp = vec2ui_dot(vec1, vec2);
		mul = dp / den;
		return (vec2ui(vec2.x * mul, vec2.y * mul));
	}
	return (vec2ui(0, 0));
}
