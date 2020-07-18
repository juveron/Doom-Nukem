/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_point_internal.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/14 10:17:00 by thboura           #+#    #+#             */
/*   Updated: 2020/07/14 10:17:07 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DELETE_POINT_INTERNAL_H
# define DELETE_POINT_INTERNAL_H

# include "doom_nukem.h"

int	free_tmp_handler(t_point *point, t_env *env, t_vector *tmp_handler,
		int ret);
int	remove_point(t_sector *sector, t_vector *tmp_handler, size_t i);
int	check_level(t_point *point, t_vector *tmp_handler, t_env *env);

#endif
