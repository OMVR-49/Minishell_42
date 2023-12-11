/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:37:55 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:50:48 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	cn(int inside, int *q)
{
	if (!*q)
		*q = inside;
	else if (*q == inside)
		*q = 0;
}

int	checking_quotes(char *l)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (l[i])
	{
		if (l[i] == '\'')
			cn(1, &j);
		else if (l[i] == '\"')
			cn(2, &j);
		i++;
	}
	return (j);
}

char	*join_one(char *str, char c)
{
	char	*s;
	char	*p;

	s = ft_malloc(2);
	s[0] = c;
	s[1] = 0;
	if (str == NULL)
		str = "";
	p = ft_strjoin(str, s);
	return (p);
}

void	check_expand_hd(t_anelement *elem)
{
	int	i;

	i = 0;
	while (elem->content[i])
	{
		if (elem->content[i] == '\'' || elem->content[i] == '\"')
		{
			elem->is_ex = 1;
			break ;
		}
		i++;
	}
}

void	quotes_handel_and_expand(t_anelement *head, t_env **all)
{
	while (head)
	{
		if (head->tk == HERE_DOC && head->next)
			check_expand_hd(head->next);
		if (head->tk == WORD)
			head->content = handler(head, all);
		head = head->next;
	}
}
