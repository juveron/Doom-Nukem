/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/21 16:53:11 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:21:51 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec2i		vec2i(int x, int y)
{
	return ((t_vec2i){.x = x, .y = y});
}

t_vec2ui	vec2ui(unsigned int x, unsigned int y)
{
	return ((t_vec2ui){.x = x, .y = y});
}

t_vec2f		vec2f(float x, float y)
{
	return ((t_vec2f){.x = x, .y = y});
}

t_vec2d		vec2d(double x, double y)
{
	return ((t_vec2d){.x = x, .y = y});
}
