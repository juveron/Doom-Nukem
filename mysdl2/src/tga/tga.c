/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:56:11 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/17 17:29:53 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"
#include <fcntl.h>
#include "tga_internal.h"

static SDL_Surface	*return_error(t_tga_handle *handle)
{
	close(handle->fd);
	SDL_FreeSurface(handle->surface);
	return (NULL);
}

static SDL_Surface	*convert_surface(t_tga *tga_file, t_tga_handle *handle)
{
	SDL_Surface	*ret;

	if (tga_file->header.pixel_depth == 24)
	{
		if (!(ret = SDL_ConvertSurfaceFormat(handle->surface,
				SDL_PIXELFORMAT_RGB888, 0)))
			return (NULL);
	}
	else
	{
		if (!(ret = SDL_ConvertSurfaceFormat(handle->surface,
				SDL_PIXELFORMAT_RGBA8888, 0)))
			return (NULL);
	}
	return (ret);
}

bool				read_right_data(t_tga *tga_file, t_tga_handle *handle)
{
	if (tga_file->header.image_type == 2)
	{
		if (!read_uncompressed_data(handle))
			return (return_error(handle));
	}
	else if (tga_file->header.image_type == 10)
		if (!read_compressed_data(handle))
			return (return_error(handle));
	return (true);
}

SDL_Surface			*import_tga(const char *path, const bool print_info)
{
	t_tga			tga_file;
	t_tga_handle	handle;
	SDL_Surface		*ret;

	ft_bzero(&handle, sizeof(t_tga_handle));
	handle.path = (char *)path;
	handle.fd = open(path, O_RDONLY);
	if (handle.fd == -1)
		return (NULL);
	if (!read_header(&handle, &tga_file, print_info)
		|| !check_and_allocate_image(&tga_file, &handle))
		return (NULL);
	read_right_data(&tga_file, &handle);
	ret = convert_surface(&tga_file, &handle);
	SDL_FreeSurface(handle.surface);
	close(handle.fd);
	return (ret);
}
