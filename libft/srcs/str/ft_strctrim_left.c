/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strctrim_left.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/20 13:39:09 by kguibout          #+#    #+#             */
/*   Updated: 2018/12/20 14:01:51 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft_str.h"

void	ft_strctrim_left(char **a_str, char const c)
{
	int		i;

	if (!a_str || !(*a_str))
		return ;
	i = 0;
	while ((*a_str)[i] == c)
	{
		(*a_str)[i] = '\0';
		i++;
	}
}
