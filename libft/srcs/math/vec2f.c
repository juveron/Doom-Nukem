/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec2f.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/23 00:15:42 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:22:19 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"

t_vec2f	vec2f_from_angle(float angle)
{
	t_vec2f	vec;

	vec.x = cosf(angle);
	vec.y = sinf(angle);
	return (vec);
}
