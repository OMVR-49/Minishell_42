/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:11 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 02:32:56 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	funco(char *line, t_cmd *com, int fd[2], t_stracto stracto)
{
	static int	i;

	line = readline(">");
	ft_lstadd_back_clctr(ft_garbege_collector(), ft_lstnew_clctr(line));
	if (!line)
	{
		if (g_end != 10)
			set_exit_status(0);
		return (i = 0, -1);
	}
	if (!ft_strcmp(com->heredoc_del[stracto.n], line) && i >= stracto.n)
		return (free(line), i = 0, close(fd[1]), 1);
	if (!ft_strcmp(com->heredoc_del[i], line))
		i++;
	else if (com->heredoc_del[1] == NULL || i == stracto.n)
	{
		if (com->expand_heredoc)
			line = expand_heredoc(line, stracto.expando);
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
	}
	return (0);
}

int	ft_heredoc(t_cmd *com, t_env **all)
{
	char		*line;
	int			fd[2];
	t_stracto	stracto;

	line = NULL;
	stracto.n = (num_d(com->heredoc_del) - 1);
	stracto.expando = all;
	if (pipe(fd) == -1)
		return (-1);
	while (1)
	{
		stracto.a = funco(line, com, fd, stracto);
		if (stracto.a == -1)
			break ;
		if (stracto.a == 1)
			return (close(fd[1]), fd[0]);
	}
	if (g_end == 10)
	{
		g_end = 5;
		return (free(line), close(fd[0]), close(fd[1]), -10);
	}
	return (free(line), close(fd[1]), fd[0]);
}

void	ft_write3(char *s1, char *s2)
{
	ft_write(2, "minishell: ");
	ft_write(2, s1);
	ft_write(2, s2);
}

int	outfile(t_cmd *com)
{
	int		fd;
	int		i;
	int		n;

	i = 0;
	n = num_d(com->outfl) - 1;
	while (com->outfl[i])
	{
		if (com->is_red_or_app == 1)
			fd = open(com->outfl[i], O_CREAT | O_TRUNC | O_RDWR, 0666);
		else if (com->is_red_or_app == 2)
			fd = open(com->outfl[i], O_RDWR | O_CREAT | O_APPEND, 0666);
		if (n != i)
		{
			close(fd);
		}
		if (access(com->outfl[i], W_OK) != 0)
		{
			ft_write3(com->outfl[i], ": Permission denied \n");
			set_exit_status(1);
			return (-1);
		}
		i++;
	}
	return (fd);
}

int	infile(t_cmd *com)
{
	int		fd;
	int		n;
	int		i;

	n = num_d(com->infl) - 1;
	i = 0;
	while (com->infl[i])
	{
		if (access(com->infl[i], F_OK) != 0)
		{
			ft_write3(com->infl[i], ":  No such file or directory \n");
			set_exit_status(1);
			return (-1);
		}
		if (access(com->infl[i], R_OK) != 0)
		{
			ft_write3(com->infl[i], ": Permission denied \n");
			set_exit_status(1);
			return (-1);
		}
		if (i == n)
			fd = open(com->infl[i], O_RDWR, 0644);
		i++;
	}
	return (fd);
}
