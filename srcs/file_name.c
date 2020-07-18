/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_name.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/06/10 10:53:19 by kguibout          #+#    #+#             */
/*   Updated: 2020/06/10 11:10:46 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "doom_nukem.h"

char	*get_file_name(char *path)
{
	char	*start;
	char	*ret;
	size_t	len;

	start = ft_strrchr(path, '/');
	if (start == NULL)
		start = path;
	else
		++start;
	len = ft_strlen(start);
	if (len <= 4)
		return (NULL);
	if (!ft_strequ(start + len - 5, ".dmap"))
		return (NULL);
	if (!(ret = ft_strsub(start, 0, len - 5)))
		return (NULL);
	return (ret);
}
