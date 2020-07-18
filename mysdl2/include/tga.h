/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:57:28 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 22:35:37 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_H
# define TGA_H

# define TGA_BUFFER_SIZE 4096

# include "libft.h"
# include <SDL2/SDL.h>

# pragma pack(push, 1)

typedef struct	s_tga_header
{
	t_u8	id_length;
	t_u8	color_map_type;
	t_u8	image_type;
	t_u16	first_entry_index;
	t_u16	color_map_length;
	t_u8	color_map_entry_size;
	t_u16	x_origin;
	t_u16	y_origin;
	t_u16	image_width;
	t_u16	image_height;
	t_u8	pixel_depth;
	t_u8	image_descriptor;
}				t_tga_header;

typedef struct	s_tga_handle
{
	int			fd;
	int			i;
	ssize_t		len_buff;
	ssize_t		remaining_bytes;
	int			image_size;
	size_t		offset;
	t_u8		buffer[TGA_BUFFER_SIZE];
	char		*path;
	int			bpp;
	SDL_Surface	*surface;
}				t_tga_handle;

typedef struct	s_tga
{
	t_tga_header	header;
	void			*data;
}				t_tga;

typedef struct	s_tga_packet
{
	bool	type;
	t_u8	number;
}				t_tga_packet;

# pragma pack(pop)

SDL_Surface		*import_tga(const char *path, const bool print_info);

#endif
