/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/23 22:48:55 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 02:27:35 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	args(t_cmd *data, t_anelement *elem, int j)
{
	int	i;

	i = 0;
	data->args[j] = (char *)ft_malloc(sizeof(char) * (ft_strlen(elem->content)
				+ 1));
	while (elem->content && elem->content[i])
	{
		data->args[j][i] = elem->content[i];
		i++;
	}
	data->args[j][i] = '\0';
}

int	in_file(t_cmd *data, t_anelement *elem)
{
	char	*tmp;
	int		i;

	if (!data->infl)
	{
		data->infl = ft_malloc(sizeof(char *) * 1);
		data->infl[0] = NULL;
	}
	i = ft_strlen(elem->content);
	if (i == 0)
	{
		elem->content = "\xf0";
		i++;
	}
	tmp = ft_malloc(sizeof(char) * (i + 2));
	tmp = ft_strncpy(elem->content, tmp, i - 1);
	tmp[i] = '\n';
	tmp[i + 1] = '\0';
	data->infl[0] = ft_strjoin(data->infl[0], tmp);
	return (1);
}

t_anelement	*outf_app(t_cmd *data, t_anelement *elem)
{
	char	*tmp;
	int		i;

	if (!data->outfl)
	{
		data->outfl = ft_malloc(sizeof(char *));
		data->outfl[0] = NULL;
	}
	i = ft_strlen(elem->content);
	if (i == 0)
	{
		elem->content = "\xf0";
		i++;
	}
	tmp = ft_malloc(sizeof(char) * (i + 2));
	tmp = ft_strncpy(elem->content, tmp, i - 1);
	tmp[i] = '\n';
	tmp[i + 1] = '\0';
	data->outfl[0] = ft_strjoin(data->outfl[0], tmp);
	return (elem);
}

int	here_doc(t_cmd *data, t_anelement *elem)
{
	char	*tmp;
	int		i;

	if (!data->heredoc_del)
	{
		data->heredoc_del = ft_malloc(sizeof(char *) * 2);
		data->heredoc_del[0] = NULL;
		data->heredoc_del[1] = NULL;
	}
	i = ft_strlen(elem->content);
	if (i == 0)
	{
		elem->content = "\xf0";
		i++;
	}
	tmp = ft_malloc(sizeof(char) * (i + 2));
	tmp = ft_strncpy(elem->content, tmp, i - 1);
	tmp[i] = '\n';
	tmp[i + 1] = '\0';
	data->heredoc_del[0] = ft_strjoin(data->heredoc_del[0], tmp);
	data->expand_heredoc = !elem->is_ex;
	return (2);
}

int	number_of_args(t_anelement *head)
{
	t_anelement	*tmp;
	int			i;

	i = 0;
	tmp = head;
	while (tmp && tmp->tk != _PIPE)
	{
		if (tmp->tk == WORD && tmp->content != NULL
			&& tmp->prev && tmp->prev->tk != APPEND && tmp->prev->tk != HERE_DOC
			&& tmp->prev->tk != RDR_IN && tmp->prev->tk != RDR_OUT)
			i++;
		tmp = tmp->next;
	}
	return (i);
}
