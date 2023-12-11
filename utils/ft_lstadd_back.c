/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/16 17:05:40 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 19:38:58 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_collector	**ft_garbege_collector(void)
{
	static t_collector	*clctr;

	return (&clctr);
}

void	*ft_malloc(size_t size)
{
	void	*ptr;

	ptr = malloc(size);
	if (!ptr)
		ft_ext(1);
	ft_lstadd_back_clctr(ft_garbege_collector(), ft_lstnew_clctr(ptr));
	return (ptr);
}

void	ft_lstadd_back_clctr(t_collector **lst, t_collector *new)
{
	t_collector	*oho;

	oho = *lst;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (oho->next != NULL)
			oho = oho->next;
		oho->next = new;
	}
}
