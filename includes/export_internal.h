/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/20 16:19:52 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/06 03:22:31 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXPORT_INTERNAL_H
# define EXPORT_INTERNAL_H

# include "doom_nukem.h"

typedef struct	s_wall_export
{
	t_u64				sector_id;
	t_unique_id			v1_id;
	t_unique_id			v2_id;
	t_vec2f				offset;
	t_vec2f				scale;
	t_vec2f				offset2;
	t_vec2f				scale2;
	float				floor;
	float				ceil;
	t_u64				neighbor;
	t_wall_location		wall_location;
}				t_wall_export;

bool			export_textures(int fd, t_env *env);
bool			export_vertices(int fd, t_doom_map *map);
bool			export_level(int fd, t_doom_map *map);
bool			export_triangle_vector(int fd, t_vector *triangle);

bool			export_objects(int fd, t_doom_map *map);
bool			exit_export_map(int fd);

#endif
