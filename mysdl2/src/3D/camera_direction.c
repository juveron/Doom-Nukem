/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_direction.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/30 14:22:20 by kguibout          #+#    #+#             */
/*   Updated: 2020/03/30 15:21:08 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "draw3d.h"

t_vec3f	camera_forward(t_camera *camera)
{
	return (vec3f(-camera->transform.rot_pos.m[2][0],
		-camera->transform.rot_pos.m[2][1],
		-camera->transform.rot_pos.m[2][2]));
}

t_vec3f	camera_left(t_camera *camera)
{
	return (vec3f(-camera->transform.rot_pos.m[0][0],
		-camera->transform.rot_pos.m[0][1],
		-camera->transform.rot_pos.m[0][2]));
}

t_vec3f	camera_up(t_camera *camera)
{
	return (vec3f(camera->transform.rot_pos.m[1][0],
		camera->transform.rot_pos.m[1][1],
		camera->transform.rot_pos.m[1][2]));
}
