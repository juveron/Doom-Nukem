/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   static_func.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/28 13:19:23 by kguibout          #+#    #+#             */
/*   Updated: 2019/05/10 11:33:27 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "func_ft_printf.h"

t_func	*static_fun(void)
{
	static t_func	func[128] = {(t_func)1};

	if (func[0] == (t_func)1)
	{
		func[0] = 0;
		func['d'] = *func_integer;
		func['s'] = *func_string;
		func['S'] = *func_wstr;
		func['i'] = *func_integer;
		func['u'] = *func_unsigned;
		func['C'] = *func_wchar;
		func['c'] = *func_char;
		func['x'] = *func_hex;
		func['%'] = *func_percent;
		func['p'] = *func_pointer;
		func['X'] = *func_hexx;
		func['o'] = *func_octal;
		func['b'] = *func_binary;
		func['r'] = *func_raw;
		func['f'] = &func_float;
	}
	return (func);
}
