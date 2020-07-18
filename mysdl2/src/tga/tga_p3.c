/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_p3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 01:21:19 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 01:21:21 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tga_internal.h"

static bool	retive_data_on_surface(t_u8 *pixels, t_u8 color[4],
		t_u8 num, t_tga_handle *handle)
{
	ssize_t	i;
	ssize_t	bytes;

	bytes = num * handle->bpp;
	i = 0;
	while (i < bytes)
	{
		if (handle->bpp == 4)
		{
			pixels[i + handle->offset] = color[0];
			pixels[i + handle->offset + 1] = color[1];
			pixels[i + handle->offset + 2] = color[2];
			pixels[i + handle->offset + 3] = color[3];
		}
		else
		{
			pixels[i + handle->offset] = color[0];
			pixels[i + handle->offset + 1] = color[1];
			pixels[i + handle->offset + 2] = color[2];
		}
		i += handle->bpp;
	}
	handle->offset += bytes;
	handle->remaining_bytes -= num;
	return (true);
}

static bool	get_color(t_tga_handle *handle, t_u8 *color)
{
	int	tmp;

	tmp = handle->len_buff - handle->i;
	if (tmp != 0)
		ft_memcpy(color, handle->buffer + handle->i, tmp);
	if (get_buffer(handle) == false || handle->len_buff < handle->bpp - tmp)
		return (false);
	ft_memcpy(color + tmp, handle->buffer, handle->bpp - tmp);
	handle->i += handle->bpp - tmp;
	return (true);
}

static bool	convert_raw_packet(t_tga_handle *handle, t_u8 *pixels,
		t_u8 num)
{
	ssize_t	bytes;

	bytes = num * handle->bpp;
	while (bytes)
	{
		if (handle->len_buff - handle->i < bytes)
		{
			ft_memcpy(pixels + handle->offset, handle->buffer + handle->i,
				handle->len_buff - handle->i);
			bytes -= handle->len_buff - handle->i;
			handle->offset += handle->len_buff - handle->i;
			get_buffer(handle);
		}
		else
		{
			ft_memcpy(pixels + handle->offset, handle->buffer + handle->i,
				bytes);
			handle->offset += bytes;
			handle->i += bytes;
			bytes = 0;
		}
	}
	handle->remaining_bytes -= num;
	return (true);
}

static bool	convert_multi_packet(t_tga_handle *handle,
		t_tga_packet *packet, t_u8 *pixels)
{
	t_u8			color[4];

	if (handle->len_buff - handle->i < handle->bpp)
	{
		if (get_color(handle, color) == false)
			return (false);
	}
	else
	{
		ft_memcpy(color, handle->buffer + handle->i, handle->bpp);
		handle->i += handle->bpp;
	}
	if (handle->remaining_bytes < packet->number)
		return (false);
	retive_data_on_surface(pixels, color, packet->number, handle);
	return (true);
}

bool		convert_data(t_tga_handle *handle)
{
	t_tga_packet	packet;
	t_u8			*pixels;

	pixels = handle->surface->pixels;
	handle->i = 0;
	while (handle->i < handle->len_buff)
	{
		packet.type = handle->buffer[handle->i] & 0x80;
		packet.number = handle->buffer[handle->i++] & 0x7F;
		packet.number++;
		if (packet.type == 1)
			convert_multi_packet(handle, &packet, pixels);
		else
		{
			if (handle->remaining_bytes < packet.number)
				return (false);
			convert_raw_packet(handle, pixels, packet.number);
		}
		if (handle->remaining_bytes == 0)
			break ;
	}
	return (true);
}
