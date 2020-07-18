/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_length.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/12 16:32:40 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/24 17:52:55 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_math.h"
#include <math.h>

float	vec3i_length(t_vec3i vec1)
{
	return (sqrtf(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z));
}

float	vec3f_length(t_vec3f vec1)
{
	return (sqrtf(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z));
}

float	vec3d_length(t_vec3d vec1)
{
	return (sqrt(vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z));
}
