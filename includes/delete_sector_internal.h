/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_sector_internal.h                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/02 14:07:01 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/02 14:29:19 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_SECTOR_INTERNAL_H
# define DELETE_SECTOR_INTERNAL_H

# include "doom_nukem.h"

bool	convert_sector2(t_sector *sector, t_vector *vertices, t_env *env);
bool	internal_set_vertex(t_handler_struct *s, t_sector *sector,
	t_env *env);
t_point	*add_vertex2(t_point *v, t_sector *sector, t_env *env);
bool	set_neighbor(t_sector *sector);

#endif
