/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material_preview_internal.h                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/05 20:30:56 by thboura           #+#    #+#             */
/*   Updated: 2020/06/05 20:34:27 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MATERIAL_PREVIEW_INTERNAL_H
# define MATERIAL_PREVIEW_INTERNAL_H

# include "doom_nukem.h"

t_u32	get_texture(SDL_Surface *texture, t_vec2f *uv);
void	draw_preview(t_gui_material_preview *mat_prev);
bool	draw_mat_prev_func(void *param);
bool	update_mat_prev_func(void *param);

#endif
