/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rasterizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/08 12:35:25 by thboura           #+#    #+#             */
/*   Updated: 2020/07/08 12:35:38 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RASTERIZER_H
# define RASTERIZER_H

# include "draw3d.h"

typedef struct	s_rasterizer
{
	int					x0;
	int					x1;
	int					y1;
	int					x;
	int					y;
	t_m128				tex;
	t_m128				tmp;
	t_m128				cmp;
	t_edges				edges;
	t_triangle_raster	corr;
	bool				in;
	float				z;
}				t_rasterizer;

void			fragment_function(t_fragment_data *data);
void			set_color(t_rasterizer *r, t_render_screen *render_screen);
void			clip_triangle(t_triangle_raster *view, t_matrix4 *m_p);
void			clip_screen(t_triangle_raster *triangle);
bool			check_if_inside(t_triangle_raster *triangle, t_tile *tile);

#endif
