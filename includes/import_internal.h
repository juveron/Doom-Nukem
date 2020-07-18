/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   import_internal.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/06 00:44:40 by thboura           #+#    #+#             */
/*   Updated: 2020/06/30 18:48:15 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IMPORT_INTERNAL_H
# define IMPORT_INTERNAL_H

# include "doom_nukem.h"
# include "export_internal.h"

SDL_Surface	*read_surface(int fd);
bool		import_triangle(int fd, t_vector *triangle);
bool		import_vertices(int fd, t_doom_map *map, t_env *env);
t_material	*import_material(int fd, t_env *env);

bool		import_wall_vector(int fd, t_doom_map *map, t_vector *wall,
	t_env *env);
bool		import_sectors(int fd, t_doom_map *map, t_env *env);

bool		import_textures(int fd, t_env *env);
bool		import_level(int fd, t_doom_map *map);
bool		import_objects(int fd, t_doom_map *map);
bool		triangulate_all_sector(t_doom_map *map);

#endif
