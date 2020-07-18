/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   float_p2.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/10 10:54:46 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:12:26 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FLOAT_P2_H
# define FLOAT_P2_H

# include "func_ft_printf.h"

int		check_nan_inf(t_printf *pf, t_string_float *string,
	t_float_func *float_func);
void	enable_sign(t_printf *pf);
void	execute_func(t_printf *pf, t_string_float *string,
	t_float_func *float_func);
#endif
