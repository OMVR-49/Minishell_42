/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_list.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/24 00:54:01 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 23:16:27 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_cmd_back(t_cmd **head, t_cmd *new)
{
	t_cmd	*tmp;

	tmp = *head;
	if (*head == NULL)
		*head = new;
	else
	{
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
	new->next = NULL;
}

int	ft_exp_here(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (str[i] != NULL)
		i++;
	while (str[i] && str[i][j])
	{
		if (str[i][j] == '\'' || str[i][j] == '\"')
			return (0);
		j++;
	}
	return (1);
}

char	**ft_split_rsb(char *s, char c)
{
	char	**result;
	int		i;

	result = ft_split(s, c);
	if (!result)
		return (NULL);
	i = 0;
	while (result[i] != NULL)
	{
		if (result[i][0] == '\xf0')
			result[i][0] = 0;
		i++;
	}
	return (result);
}

void	finish_them(t_cmd *data, t_anelement *apin, int j)
{
	if (data->outfl)
	{
		if (apin->prev && apin->prev->tk == APPEND)
			data->is_red_or_app = 2;
		else if (apin->prev && apin->prev->tk == RDR_OUT)
			data->is_red_or_app = 1;
		data->outfl = ft_split_rsb(data->outfl[0], '\n');
	}
	if (data->infl)
		data->infl = ft_split_rsb(data->infl[0], '\n');
	if (data->heredoc_del)
		data->heredoc_del = ft_split_rsb(data->heredoc_del[0], '\n');
	data->h_i = j;
}

int	diff_to(t_anelement *elem)
{
	if (!elem->prev)
		return (1);
	if (elem->prev && elem->prev->tk != HERE_DOC && elem->prev->tk != RDR_IN
		&& elem->prev->tk != RDR_OUT && elem->prev->tk != APPEND)
		return (1);
	return (0);
}
