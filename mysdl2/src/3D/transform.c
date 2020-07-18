/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transform.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 02:21:01 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/30 11:24:30 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include "draw3d.h"
#include <fcntl.h>
#include <math.h>

void	update_transform(t_transform *transform)
{
	t_matrix4	tmp;

	matrix_scale(transform->scale.x, transform->scale.y, transform->scale.z,
		&transform->rot_pos_scale);
	matrix_rotation(transform->rotation.x, transform->rotation.y,
		transform->rotation.z, &tmp);
	ft_memcpy(&transform->rot_pos, &tmp, sizeof(t_matrix4));
	transform->rot_pos_scale = matrix_multiply(&transform->rot_pos_scale, &tmp);
	matrix_translation(transform->position.x, transform->position.y,
		transform->position.z, &tmp);
	transform->rot_pos_scale = matrix_multiply(&transform->rot_pos_scale, &tmp);
	transform->rot_pos = matrix_multiply(&transform->rot_pos, &tmp);
}
