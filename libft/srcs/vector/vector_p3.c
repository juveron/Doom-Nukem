/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector_p3.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/21 16:36:25 by kguibout          #+#    #+#             */
/*   Updated: 2020/01/22 09:42:48 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "internal/libft_vector_internal.h"

void	*vector_back(t_vector *da)
{
	return (vector_get(da, da->total - 1));
}

bool	vector_insert(t_vector *da, size_t index, void *item)
{
	if (index <= da->total)
	{
		if (da->capacity == da->total)
		{
			if (!vector_resize(da, da->capacity * 2))
				return (false);
		}
		if (index != da->total)
		{
			ft_memmove(da->items + (index + 1) * da->sizeof_elem,
				da->items + index * da->sizeof_elem,
				da->sizeof_elem * (da->total - index));
		}
		ft_memcpy(da->items + index * da->sizeof_elem, item, da->sizeof_elem);
		++da->total;
	}
	return (true);
}

bool	vector_join(t_vector *vec1, t_vector *vec2)
{
	size_t	new_capacity;
	size_t	tmp_total;

	if (vec1->sizeof_elem != vec2->sizeof_elem)
		return (false);
	tmp_total = vec1->total;
	new_capacity = vec1->capacity;
	if (new_capacity < vec2->total + vec1->total)
	{
		while (new_capacity < vec2->total + vec1->total)
			new_capacity *= 2;
		if (!vector_resize(vec1, new_capacity))
			return (false);
	}
	ft_memcpy(vec1->items + tmp_total * vec1->sizeof_elem, vec2->items,
		vec2->total * vec2->sizeof_elem);
	vec1->total += vec2->total;
	return (true);
}

bool	vector_append_array(t_vector *vector, void *array,
	size_t number_of_elem)
{
	size_t	new_capacity;

	new_capacity = vector->capacity;
	while (new_capacity < number_of_elem + vector->total)
		new_capacity *= 2;
	if (!vector_resize(vector, new_capacity))
		return (false);
	ft_memmove(vector->items + vector->total * vector->sizeof_elem, array,
		number_of_elem * vector->sizeof_elem);
	vector->total += number_of_elem;
	return (true);
}

bool	vector_clone(t_vector *src, t_vector *dst)
{
	if (!vector_init(dst, src->sizeof_elem))
		return (false);
	if (!vector_resize(dst, src->capacity))
	{
		vector_free(dst);
		return (false);
	}
	ft_memmove(dst->items, src->items,
		src->total * src->sizeof_elem);
	dst->total = src->total;
	return (true);
}
