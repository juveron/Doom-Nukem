/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/27 13:33:13 by kguibout          #+#    #+#             */
/*   Updated: 2019/01/14 14:49:05 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	size_s;
	char	*new_str;

	size_s = ft_strlen(s);
	if ((new_str = (char *)malloc(size_s + 1)) == NULL)
		return (NULL);
	ft_strcpy(new_str, s);
	return (new_str);
}
