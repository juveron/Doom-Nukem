/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_p2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 01:21:14 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 01:21:14 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga.h"

bool		get_buffer(t_tga_handle *handle)
{
	ssize_t	ret;

	ret = read(handle->fd, handle->buffer, TGA_BUFFER_SIZE);
	if (ret <= 0)
	{
		ft_dprintf(2, "Invalid tga file ! (%s)\n", handle->path);
		return (false);
	}
	handle->i = 0;
	handle->len_buff = ret;
	return (true);
}

static bool	create_bgr_surface(t_tga_handle *handle,
		t_tga_header *tga_header)
{
	if (!(handle->surface = SDL_CreateRGBSurfaceWithFormat(0,
		tga_header->image_width, tga_header->image_height, 24,
		SDL_PIXELFORMAT_BGR24)))
	{
		ft_dprintf(2, "Fail to allocate TGA surface !\n");
		return (false);
	}
	return (true);
}

static bool	create_bgra_surface(t_tga_handle *handle,
										t_tga_header *tga_header)
{
	if (!(handle->surface = SDL_CreateRGBSurfaceWithFormat(0,
		tga_header->image_width, tga_header->image_height, 32,
		SDL_PIXELFORMAT_BGRA32)))
	{
		ft_dprintf(2, "Fail to allocate TGA surface !\n");
		return (false);
	}
	return (true);
}

static bool	create_right_surface(t_tga_header *tga_header,
		t_tga_handle *handle)
{
	if (tga_header->pixel_depth == 24)
	{
		if (!create_bgr_surface(handle, tga_header))
			return (false);
	}
	else if (tga_header->pixel_depth == 32)
	{
		if (!create_bgra_surface(handle, tga_header))
			return (false);
	}
	else
	{
		ft_dprintf(2, "Failed to open TGA file only 24 and 32 bits pixels \
			format are supported ! (%s)\n", handle->path);
		return (false);
	}
	handle->bpp = tga_header->pixel_depth / 8;
	return (true);
}

bool		check_and_allocate_image(t_tga *tga_file,
		t_tga_handle *handle)
{
	if (tga_file->header.image_type != 2 && tga_file->header.image_type != 10)
	{
		ft_dprintf(2, "Only tga image type 2 and 10 are supported !\n");
		close(handle->fd);
		return (false);
	}
	if (!create_right_surface(&tga_file->header, handle))
	{
		close(handle->fd);
		return (false);
	}
	return (true);
}
