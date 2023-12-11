/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:25:55 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/07 13:00:02 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	word_push(char *l, t_anelement **elem, int i, t_anelement **h)
{
	int	k;

	k = 0;
	while (l[i] && k == 0)
	{
		while (!ft_is_special(l[i]))
		{
			i++;
			k = 1;
		}
		if (l[i] == '\'' || l[i] == '\"')
		{
			if (l[i] == '\'')
				while (l[++i] != '\'')
					;
			else if (l[i] == '\"')
				while (l[++i] != '\"')
					;
			k = 0;
			i++;
		}
		if (l[i] == '<' || l[i] == '>' || l[i] == '|')
			break ;
	}
	return (element(elem, l, i, h), (*elem)->len);
}

void	tokenize1(int i, char *l, t_anelement **h)
{
	t_anelement	*elem;

	elem = NULL;
	while (l[i])
	{
		if (!ft_is_special(l[i]) || l[i] == '\'' || l[i] == '\"')
			i += word_push(&l[i], &elem, 0, h);
		else if (l[i] == '<')
			i += rdr_in_push(&l[i], &elem, 0, h);
		else if (l[i] == '>')
			i += rdr_out_push(&l[i], &elem, 0, h);
		else if (l[i] == '|')
			i += pipe_push(&l[i], &elem, 0, h);
	}
}

void	tokenize(t_anelement **head, char	**splited)
{
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (splited[j])
	{
		tokenize1(i, splited[j], head);
		j++;
	}
}
