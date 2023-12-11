/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:35:41 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 05:07:51 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	numberofpipes(t_anelement *head_a)
{
	int	i;

	i = 0;
	while (head_a != NULL)
	{
		if (head_a && head_a->tk == _PIPE)
			i++;
		head_a = head_a->next;
	}
	return (i);
}

int	jaja(int *i, t_anelement **apin, t_cmd **node, int k)
{
	(*i) = -1;
	*apin = NULL;
	*node = (t_cmd *)ft_calloc(sizeof(t_cmd), 1);
	(*node)->heredoc_del = NULL;
	(*node)->infl = NULL;
	(*node)->outfl = NULL;
	(*node)->args = (char **)ft_malloc(sizeof(char *) * (k + 1));
	return (0);
}

t_anelement	*cmds1(t_cmd **head, t_anelement *elem, int k)
{
	t_anelement		*apin;
	t_cmd			*node;
	int				i;
	int				j;

	j = jaja(&i, &apin, &node, k);
	while (elem != NULL && elem->tk != _PIPE)
	{
		if (elem->tk == WORD && elem->content && diff_to(elem))
			args(node, elem, ++i);
		else if (elem->tk == RDR_IN)
			j = in_file(node, elem->next);
		else if (elem->tk == APPEND || elem->tk == RDR_OUT)
			apin = outf_app(node, elem->next);
		else if (elem->tk == HERE_DOC)
			j = here_doc(node, elem->next);
		elem = elem->next;
	}
	node->args[++i] = NULL;
	finish_them(node, apin, j);
	ft_cmd_back(head, node);
	if (elem && elem->tk == _PIPE)
		return (elem->next);
	else
		return (elem);
}

void	cmds(t_cmd **head, t_anelement *head_a, int i)
{
	int		j;

	j = 0;
	while (j < i)
	{
		head_a = cmds1(head, head_a, number_of_args(head_a) + 1);
		j++;
	}
}

t_cmd	*parser(char *l, t_env **all)
{
	char			**splited;
	t_anelement		*head_a;
	t_cmd			*head_c;
	int				i;
	int				j;

	(void)all;
	i = 0;
	j = 0;
	head_a = NULL;
	head_c = NULL;
	l = ft_strtrim (l, " ");
	i = wordc(l);
	splited = ft_split2(l);
	tokenize(&head_a, splited);
	i = syntax_error(head_a);
	if (i)
	{
		syntax_errors_return_status(i);
		return (NULL);
	}
	quotes_handel_and_expand(head_a, all);
	i = numberofpipes(head_a) + 1;
	cmds(&head_c, head_a, i);
	return (head_c);
}
