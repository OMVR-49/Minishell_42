/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe5.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:31 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 03:47:28 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*full_line(char *env)
{
	char	*line;
	int		i;

	line = ft_malloc(ft_strlen(env) + 1);
	i = 0;
	while (env[i])
	{
		line[i] = env[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

void	make_node(t_env **all, char *val, char *name, char *line)
{
	t_env	*node;
	t_env	*tmp;

	node = ft_malloc(sizeof(t_env));
	node->val = val;
	node->name = name;
	node->line = line;
	node->next = NULL;
	if (*all == NULL)
	{
		*all = node;
	}
	else
	{
		tmp = *all;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		}
		tmp->next = node;
	}
}

void	here_beg(t_cmd *com, t_env **all)
{
	t_cmd	*tmp;
	int		l;

	tmp = com;
	while (tmp)
	{
		tmp->fd_heredoc = -1;
		if (tmp->heredoc_del)
		{
			l = ft_heredoc(tmp, all);
			if (l == -1)
			{
				exit(1);
			}
			tmp->fd_heredoc = l;
		}
		tmp = tmp->next;
	}
}

void	return_val(int status)
{
	if (WIFEXITED(status))
		set_exit_status(WEXITSTATUS(status));
	else if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == 3)
			set_exit_status(131);
		else if (WTERMSIG(status) == 2)
			set_exit_status(130);
	}
}

int	wait_all(int **pips, t_cmd *tmp, t_cmd *tmp3, int n)
{
	int	status;
	int	yy;

	status = 0;
	while (tmp && tmp->next)
		tmp = tmp->next;
	yy = waitpid(tmp->pid, &status, 0);
	if (yy != -1)
		return_val(status);
	close_all(pips, n);
	while (wait(NULL) != -1)
		;
	while (tmp3)
	{
		if (tmp3->fd_heredoc != -1)
			close(tmp3->fd_heredoc);
		tmp3 = tmp3->next;
	}
	return (0);
}
