/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   save_bmp.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/15 21:41:37 by marvin            #+#    #+#             */
/*   Updated: 2019/07/19 12:36:50 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include "bmp.h"

static t_bmp	*data_to_bmp_pixel(int *pixel_data, int width, int height)
{
	t_bmp	*bmp;
	int		x;
	int		y;

	if (!(bmp = (t_bmp *)ft_memalloc(sizeof(*bmp))))
		return (NULL);
	if (!(bmp->data = (int *)malloc(sizeof(int) * width * height)))
	{
		free(bmp);
		return (NULL);
	}
	y = 0;
	while (y < height)
	{
		x = 0;
		while (x < width)
		{
			bmp->data[x + (height - 1 - y) * width] =
				(pixel_data[x + y * width] | 0xFF000000);
			x++;
		}
		y++;
	}
	return (bmp);
}

static int		close_fd(int fd, int code, t_bmp *bmp)
{
	if (bmp)
	{
		if (bmp->data)
			free(bmp->data);
		free(bmp);
	}
	if (fd >= 0)
		close(fd);
	return (code);
}

int				save_bmp(char *path, int *pixel_data, int width, int height)
{
	int					fd;
	t_bmp				*bmp;
	t_bmp_file_header	header_file;

	fd = -1;
	if (!path || !pixel_data
		|| (fd = open(path, O_RDWR | O_TRUNC | O_CREAT, 00600)) < 0)
		return (close_fd(fd, -1, NULL));
	header_file = (t_bmp_file_header){.file_type = 0x4D42,
		.file_size = 70 + width * height, .reserved = 0, .offset = 70};
	if (!(bmp = data_to_bmp_pixel(pixel_data, width, height)))
		return (close_fd(fd, -1, NULL));
	bmp->info = (t_bmp_info_header){.header_size = 56, .width = width,
		.height = height, .planes = 1, .bpp = 32, .compression = 3,
		.raw_size = 4 * width * height, .x_res = 0, .y_res = 0,
		.color_palette = 0, .blue_mask = 0xFF, .green_mask = 0xFF00,
		.red_mask = 0xFF0000, .alpha_mask = 0xFF000000};
	if ((write(fd, &header_file, sizeof(header_file))) < 0
		|| (write(fd, &bmp->info, sizeof(bmp->info))) < 0
		|| (write(fd, bmp->data, sizeof(int) * height * width)) < 0)
		return (close_fd(fd, -1, bmp));
	return (close_fd(fd, 0, bmp));
}
