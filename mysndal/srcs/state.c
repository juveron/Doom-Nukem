/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   state.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/31 17:38:31 by thboura           #+#    #+#             */
/*   Updated: 2020/03/31 19:22:28 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mysndal.h"

bool	set_distance_model(ALenum model)
{
	alDistanceModel(model);
	return (verify_error());
}
