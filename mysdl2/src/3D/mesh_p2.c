/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mesh_p2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/29 21:16:45 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/03 11:56:39 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysdl2.h"

void	destroy_mesh(t_mesh **mesh)
{
	if (!*mesh)
		return ;
	mtl_destroy(&(*mesh)->default_material);
	vector_free(&(*mesh)->render_objects);
	free((*mesh)->name);
	vector_free(&(*mesh)->vertex);
	ft_memdel((void **)mesh);
}
