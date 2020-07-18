/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log10.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/25 10:37:39 by kguibout          #+#    #+#             */
/*   Updated: 2019/03/27 21:21:18 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

long	ft_log10(long n)
{
	int	ret;

	ret = 0;
	while (n > 9)
	{
		ret += 1;
		n /= 10;
	}
	return (ret);
}