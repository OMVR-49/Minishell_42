/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_list.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 10:53:25 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 23:02:16 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_anelemtadd_back(t_anelement **head, t_anelement *new)
{
	t_anelement	*tmp;

	tmp = *head;
	if (*head == NULL)
	{
		*head = new;
		new->prev = NULL;
	}
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
		new->prev = tmp;
	}
	new->next = NULL;
}

t_anelement	*ft_anelement_new(void)
{
	t_anelement	*p;

	p = (t_anelement *)ft_malloc(sizeof(t_anelement));
	if (!p)
		return (0);
	ft_lstadd_back_clctr(ft_garbege_collector(), ft_lstnew_clctr(p));
	p->next = NULL;
	return (p);
}

void	element(t_anelement **elem, char *l, int i, t_anelement **h)
{
	int	j;

	j = i;
	(*(elem)) = (t_anelement *)ft_malloc(sizeof(t_anelement));
	(*(elem))->tk = type(elem, l, 0);
	(*(elem))->content = (char *)ft_malloc(sizeof(char) * (i + 1));
	i = 0;
	while (l[i] && i < j)
	{
		(*(elem))->content[i] = l[i];
		i++;
	}
	(*(elem))->content[i] = '\0';
	(*(elem))->len = j;
	(*(elem))->is_ex = 0;
	ft_anelemtadd_back(h, *elem);
}
