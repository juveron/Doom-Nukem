/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bmp.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 21:42:32 by marvin            #+#    #+#             */
/*   Updated: 2019/07/19 15:35:45 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BMP_H
# define BMP_H

# include "libft.h"

# pragma pack(push, 1)

typedef struct	s_bmp_file_header
{
	t_u16	file_type;
	t_u32	file_size;
	t_u32	reserved;
	t_u32	offset;
}				t_bmp_file_header;

typedef struct	s_bmp_info_header
{
	t_u32	header_size;
	t_u32	width;
	t_u32	height;
	t_u16	planes;
	t_u16	bpp;
	t_u32	compression;
	t_u32	raw_size;
	t_u32	x_res;
	t_u32	y_res;
	t_u32	color_palette;
	t_u32	color_important;
	t_u32	red_mask;
	t_u32	green_mask;
	t_u32	blue_mask;
	t_u32	alpha_mask;
}				t_bmp_info_header;

# pragma pack(pop)

typedef	struct	s_bmp
{
	t_bmp_info_header	info;
	int					*data;
}				t_bmp;

int				save_bmp(char *path, int *pixel_data, int width, int height);

#endif
