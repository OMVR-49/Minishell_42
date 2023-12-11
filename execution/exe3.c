/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe3.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:17 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:40:19 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	in_pipe(int **pips, int i)
{
	int	fd;

	fd = pips[i - 1][0];
	dup2(fd, 0);
	close(fd);
	close(pips[i - 1][1]);
}

int	in_com(t_cmd *com, int **pips, int i)
{
	int	fd;

	fd = 0;
	if (com->infl || com->heredoc_del)
	{
		if (com->infl)
		{
			fd = infile(com);
			if (fd == -1)
				return (fd);
			dup2(fd, 0);
			close(fd);
		}
		if (com->h_i == 2)
		{
			dup2(com->fd_heredoc, 0);
			close(com->fd_heredoc);
		}
	}
	else if (i > 0)
		in_pipe(pips, i);
	return (1);
}

int	out_com(t_cmd *com, int **pips, int n, int i)
{
	int	fd;

	if (com->outfl)
	{
		fd = outfile(com);
		if (fd == -1)
			return (fd);
		dup2(fd, 1);
		close(fd);
	}
	else if (i < n - 1)
	{
		dup2(pips[i][1], 1);
		close(pips[i][1]);
		close(pips[i][0]);
	}
	return (0);
}

int	**alloc_pipes(int n)
{
	int	**pips;
	int	i;

	i = 0;
	pips = (int **)ft_malloc(sizeof(int *) * (n - 1));
	if (!pips)
		exit(1);
	while (i < n - 1)
	{
		pips[i] = (int *)ft_malloc(sizeof(int) * 2);
		if (!pips[i])
			exit(1);
		i++;
	}
	return (pips);
}

void	close_all(int **pips, int n)
{
	int	i;

	i = 0;
	while (i < (n - 1))
	{
		close(pips[i][0]);
		close(pips[i][1]);
		i++;
	}
}
