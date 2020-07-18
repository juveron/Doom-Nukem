/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sector_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/30 12:58:47 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 13:02:13 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SECTOR_INTERNAL_H
# define SECTOR_INTERNAL_H

# include "doom_nukem.h"

void		set_null_materials(t_vector *walls);
bool		set_material_internal(t_wall *wall, t_wall *old_wall, size_t i);
void		set_wall_point(t_wall *wall, t_vector *new_walls,
	t_point **point_array, size_t i);
bool		internal_vertices_clone(t_sector *sector, t_vector *vertices);

#endif
