/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vec3_length_sq.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: killian <killian@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/14 12:46:07 by kguibout          #+#    #+#             */
/*   Updated: 2019/10/24 16:35:18 by killian          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

float	vec3i_length_sq(t_vec3i vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
}

float	vec3f_length_sq(t_vec3f vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
}

float	vec3d_length_sq(t_vec3d vec1)
{
	return (vec1.x * vec1.x + vec1.y * vec1.y + vec1.z * vec1.z);
}
