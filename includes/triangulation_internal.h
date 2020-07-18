/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   triangulation_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:10:51 by thboura           #+#    #+#             */
/*   Updated: 2020/06/06 00:14:31 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TRIANGULATION_INTERNAL_H
# define TRIANGULATION_INTERNAL_H

# include "doom_nukem.h"

t_u64	get_most_left_vertex(t_vector *polygon);
t_u32	get_farthest_vertex(t_vector *polygon, t_u64 left);

bool	compute_triangulation(t_vector *polygon, t_vector *triangle);

void	set_top_triangle(t_wall *wall, t_sector *sector);
void	set_bottom_triangle(t_wall *wall, t_sector *sector);
void	set_full_triangle(t_wall *wall, t_sector *sector);

void	flip_triangle(t_triangle *triangle);
bool	compute_triangulation_p5(t_vector new_polygon[2],
										t_vector *triangle);
#endif
