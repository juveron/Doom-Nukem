/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_obj_internal.h                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 12:35:00 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 12:35:00 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPEN_OBJ_INTERNAL_H
# define OPEN_OBJ_INTERNAL_H

# include "draw3d.h"

bool	init_obj_file(t_obj_file *obj);
size_t	count_tab(char **tab);
bool	make_face(char **str, t_obj_file *obj);
int		open_file(char *path);
void	*free_obj(t_obj_file *obj);
bool	make_vertex_texture(char **str, t_obj_file *obj);
bool	make_vertex(char **str, t_obj_file *obj);
void	*free_mesh_and_obj(t_mesh *mesh, t_obj_file *obj);

#endif
