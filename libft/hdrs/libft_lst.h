/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_lst.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thboura <thboura@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/07 14:46:34 by kguibout          #+#    #+#             */
/*   Updated: 2020/05/30 21:18:57 by thboura          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIBFT_LST_H
# define LIBFT_LST_H

# include "libft.h"

typedef struct s_list	t_list;

struct					s_list
{
	void	*content;
	size_t	content_size;
	t_list	*next;
};

typedef struct s_dlist	t_dlist;

typedef struct			s_dlist_handler
{
	t_dlist	*head;
	t_dlist	*tail;
	size_t	size;
}						t_dlist_handler;

struct					s_dlist
{
	void		*content;
	size_t		content_size;
	t_dlist		*next;
	t_dlist		*prev;
};

void					ft_lstadd(t_list **alst, t_list *new);
void					ft_lstaddend(t_list **alst, t_list *new);
void					ft_lstdel(t_list **alst, void (*del)(void *, size_t));
void					ft_lstdelone(t_list **alst, void (*del)(void *,
	size_t));
void					ft_lstiter(t_list *lst, void (*f)(t_list *elem));
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));
t_list					*ft_lstnew(const void *content, size_t content_size);
t_list					*ft_lstmap(t_list *lst, t_list *(*f)(t_list *elem));

t_dlist_handler			*ft_dlist_create(void);
t_dlist					*ft_dlistaddend(t_dlist_handler *dlist_handler,
	t_dlist *node);
t_dlist					*ft_dlistaddfront(t_dlist_handler *dlist_handler,
	t_dlist *node);
void					ft_dlistdel(t_dlist_handler **dlist_handler,
	void (*del)(void *));
t_dlist					*ft_dlistnew(const void *content, size_t content_size);
void					ft_dlistdelone(t_dlist_handler *dlist_handler,
	t_dlist *list, void (*del)(void *));
t_dlist					*ft_dlist_insert(t_dlist_handler *handler,
	t_dlist *node, t_dlist *new);
t_dlist					*ft_dlist_get_by_index(t_dlist_handler *list,
	size_t index);
size_t					ft_dlist_get_index(t_dlist_handler *list,
	t_dlist *dlist);

#endif
