/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textfield_p2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/07/01 15:01:23 by kguibout          #+#    #+#             */
/*   Updated: 2020/07/01 15:01:24 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "textfield_internal.h"

bool	textfield_change_limit(t_gui_textfield *textfield,
		t_u64 limit)
{
	char	*text;

	textfield->text_size_limit = limit;
	if (textfield->text_size > limit)
	{
		if (!(text = ft_strsub(textfield->text, 0, limit)))
			return (false);
		free(textfield->text);
		textfield->text = text;
		textfield->need_redraw = true;
	}
	return (true);
}

bool	textfield_change_value(t_gui_textfield *textfield,
		char *value)
{
	size_t	size;

	size = ft_strlen(value);
	free(textfield->text);
	if (size > textfield->text_size_limit)
	{
		if (!(textfield->text = ft_strsub(value, 0,
				textfield->text_size_limit)))
			return (false);
		textfield->text_size = textfield->text_size_limit;
	}
	else
	{
		if (!(textfield->text = ft_strdup(value)))
			return (false);
		textfield->text_size = size;
	}
	textfield->need_redraw = true;
	textfield->component.need_redraw = true;
	return (true);
}

bool	textfield_change_default_text(t_gui_textfield *textfield,
		char *default_text)
{
	free(textfield->default_text);
	if (!(textfield->default_text = ft_strdup(default_text)))
		return (false);
	textfield->need_redraw = true;
	return (true);
}
