/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/15 03:15:18 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 03:07:16 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_collector	*ft_lstnew_clctr(void *l3iba)
{
	t_collector	*p;

	p = (t_collector *)malloc(sizeof(t_collector));
	if (!p)
		return (0);
	p->ptr = l3iba;
	p->next = 0;
	return (p);
}
