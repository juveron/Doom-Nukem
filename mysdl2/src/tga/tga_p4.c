/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_p4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 01:21:26 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 01:21:26 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_internal.h"

static void	copy_data(t_tga_handle *handle, ssize_t *i)
{
	ft_memcpy(handle->surface->pixels + *i, handle->buffer,
			handle->image_size - *i);
	*i = handle->image_size;
}

bool		read_uncompressed_data(t_tga_handle *handle)
{
	ssize_t	ret;
	ssize_t	i;

	i = 0;
	handle->image_size = handle->surface->h * handle->surface->pitch;
	while (i < handle->image_size)
	{
		ret = read(handle->fd, handle->buffer, TGA_BUFFER_SIZE);
		if (ret < TGA_BUFFER_SIZE && handle->image_size - i > ret)
		{
			ft_dprintf(2, "Invalid tga file ! (%s)\n",
					handle->path);
			return (false);
		}
		if (i + ret > handle->image_size)
			copy_data(handle, &i);
		else
		{
			ft_memcpy(handle->surface->pixels + i, handle->buffer, ret);
			i += ret;
		}
	}
	return (true);
}

static void	print_tga_header_info(t_tga_header *header)
{
	ft_printf("ID Length: %hhd\n", header->id_length);
	ft_printf("Color Map Type: %hhd\n", header->color_map_type);
	ft_printf("Image Type: %hhd\n", header->image_type);
	ft_printf("First Entry Index: %hd\n", header->first_entry_index);
	ft_printf("Color Map Length: %hd\n", header->color_map_length);
	ft_printf("Color Map Entry Size: %hhd\n", header->color_map_entry_size);
	ft_printf("X Origin: %hd\n", header->x_origin);
	ft_printf("Y Origin: %hd\n", header->y_origin);
	ft_printf("Image Width: %hd\n", header->image_width);
	ft_printf("Image Height: %hd\n", header->image_height);
	ft_printf("Pixel Depth: %hhd\n", header->pixel_depth);
	ft_printf("Image Descriptor: %hhd\n", header->image_descriptor);
}

bool		read_header(t_tga_handle *handle, t_tga *tga_file,
		bool print_info)
{
	if (read(handle->fd, &tga_file->header,
			sizeof(t_tga_header)) < (ssize_t)sizeof(t_tga_header))
	{
		ft_dprintf(2, "Invalid tga file ! (%s)\n", handle->path);
		close(handle->fd);
		return (false);
	}
	if (print_info)
		print_tga_header_info(&tga_file->header);
	return (true);
}

bool		read_compressed_data(t_tga_handle *handle)
{
	handle->remaining_bytes = handle->surface->h * handle->surface->w;
	handle->image_size = handle->remaining_bytes;
	while (handle->remaining_bytes != 0)
	{
		if (get_buffer(handle) == false
			|| convert_data(handle) == false)
			return (false);
	}
	return (true);
}
