/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin_free.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/12 12:00:16 by kguibout          #+#    #+#             */
/*   Updated: 2019/12/12 13:51:46 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_free(char *s1, char *s2, t_u8 num_param)
{
	char	*str;

	str = NULL;
	if (s1 != NULL && s2 != NULL)
	{
		if ((str = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)) == NULL)
			return (NULL);
		ft_strcpy(str, s1);
		ft_strcat(str, s2);
	}
	else if (s1 != NULL)
		str = ft_strdup(s1);
	else if (s2 != NULL)
		str = ft_strdup(s2);
	if (num_param == 1 || num_param == 3)
		free(s1);
	if (num_param == 2 || num_param == 3)
		free(s2);
	return (str);
}
