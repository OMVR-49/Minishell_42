/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/14 22:53:31 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/05 23:12:10 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

enum e_tokenizing	type(t_anelement **elem, char *l, int i)
{
	if (l[i] == '<')
	{
		if (l[i + 1] && l[1 + i] == '<')
			(*elem)->tk = HERE_DOC;
		else
			(*elem)->tk = RDR_IN;
	}
	else if (l[i] == '>')
	{
		if (l[i + 1] && l[1 + i] == '>')
			(*elem)->tk = APPEND;
		else
			(*elem)->tk = RDR_OUT;
	}
	else if (l[i] == '|')
		(*elem)->tk = _PIPE;
	else
		(*elem)->tk = WORD;
	return ((*elem)->tk);
}

int	rdr_out_push(char *l, t_anelement **elem, int i, t_anelement **h)
{
	if (l[i + 1] && l[1 + i] == '>')
		element(elem, l, ++i + 1, h);
	else
		element(elem, l, ++i, h);
	return ((*elem)->len);
}

int	rdr_in_push(char *l, t_anelement **elem, int i, t_anelement **h)
{
	if (l[i + 1] && l[1 + i] == '<')
		element(elem, l, ++i + 1, h);
	else
		element(elem, l, ++i, h);
	return ((*elem)->len);
}

int	pipe_push(char *l, t_anelement **elem, int i, t_anelement **h)
{
	if (l[i] == _PIPE)
		i++;
	element(elem, l, i, h);
	return ((*elem)->len);
}

int	q_dq_push(char *l, t_anelement **elem, int i, t_anelement **h)
{
	while (l[i])
	{
		if (l[i] == '\'')
		{
			while (l[i])
				i++;
			element(elem, l, i, h);
		}
		else if (l[i] == '\"')
		{
			while (l[i])
				i++;
			element(elem, l, i, h);
		}
	}
	return ((*elem)->len);
}
