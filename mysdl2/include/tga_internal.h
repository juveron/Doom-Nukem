/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tga_internal.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/16 02:18:57 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/16 02:18:57 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TGA_INTERNAL_H
# define TGA_INTERNAL_H

# include "tga.h"

bool	check_and_allocate_image(t_tga *tga_file,
			t_tga_handle *handle);
bool	read_compressed_data(t_tga_handle *handle);
bool	get_buffer(t_tga_handle *handle);
bool	read_uncompressed_data(t_tga_handle *handle);
bool	read_header(t_tga_handle *handle, t_tga *tga_file,
		bool print_info);
bool	convert_data(t_tga_handle *handle);

#endif
