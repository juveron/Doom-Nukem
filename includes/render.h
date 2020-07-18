/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 23:19:11 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/30 18:48:37 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RENDER_H
# define RENDER_H

# include "libft.h"
# include "doom_nukem.h"

typedef struct	s_pvs_handle
{
	bool		available;
	t_vec3f		start1;
	t_vec3f		end1;
	t_vec3f		start2;
	t_vec3f		end2;
	t_sector	*sector;
	int			iter;
}				t_pvs_handle;

typedef struct	s_pvs_handle_2
{
	t_wall			*wall;
	t_wall			*wall_i;
	float			check[4];
	t_vector		*vector;
	t_sector		*sector;
	t_pvs_handle	s;
}				t_pvs_handle_2;

bool			compute_all_pvs(t_env *env);
bool			compute_pvs_internal(t_pvs_handle_2 *pvs);
bool			compute_pvs(t_sector *sector,
		t_vector *vector);

#endif
