/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strappend.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/18 13:41:06 by kguibout          #+#    #+#             */
/*   Updated: 2018/12/20 13:34:51 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strappend(char **dst, const char *src)
{
	char	*tmp;

	tmp = ft_strjoin(*dst, src);
	ft_strdel(dst);
	*dst = tmp;
	return (*dst);
}
