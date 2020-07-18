/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_vector.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kguibout <kguibout@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/20 00:42:57 by kguibout          #+#    #+#             */
/*   Updated: 2020/04/13 09:55:47 by kguibout         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_VECTOR_H
# define LIBFT_VECTOR_H

# include <stdlib.h>
# include <stdbool.h>
# define VECTOR_INIT_CAPACITY	4

/*
** Structure for dynamic array
**
** !!!!! Be careful !!!! it is not recommended to store the pointer of items or
** storing the pointer return by vector_get if you add elements to the array
** because the pointer address will change in case of reallocation.
*/

typedef struct			s_vector
{
	void	*items;
	size_t	capacity;
	size_t	total;
	size_t	sizeof_elem;
}						t_vector;

bool					vector_init(t_vector *vector, size_t sizeof_elem);
int						vector_total(t_vector *vector);
bool					vector_push(t_vector *vector, void *item);
void					vector_set(t_vector *vector, size_t index,
							void *item);
void					*vector_get(t_vector *vector, size_t index);
bool					vector_delete(t_vector *vector, size_t index);
void					vector_free(t_vector *vector);
void					*vector_back(t_vector *vector);
bool					vector_pop(t_vector *vector);
bool					vector_insert(t_vector *vector, size_t index,
							void *item);
bool					vector_join(t_vector *vec1, t_vector *vec2);
bool					vector_append_array(t_vector *vector, void *array,
							size_t number_of_elem);
bool					vector_clone(t_vector *src, t_vector *dst);
bool					vector_init_n(t_vector *vector, size_t sizeof_elem,
	size_t numof_elem);

#endif
