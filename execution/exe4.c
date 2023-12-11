/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe4.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:24 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 03:46:51 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	**env_to_char(t_env *env)
{
	int		i;
	char	**str;
	t_env	*tmp;

	tmp = env;
	i = 0;
	if (!env)
		return (NULL);
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	str = (char **)(ft_malloc(sizeof(char *) * (i + 1)));
	i = 0;
	tmp = env;
	while (tmp)
	{
		str[i] = ft_strdup(tmp->line);
		tmp = tmp->next;
		i++;
	}
	str[i] = NULL;
	return (str);
}

void	exc2(char *path, t_cmd *com, char **env)
{
	if (path != NULL && *com->args[0])
	{
		execve(path, com->args, env);
		ft_write(2, "minishell: ");
		ft_write(2, com->args[0]);
		ft_write(2, ":  command not found\n");
		exit(127);
	}
	else if (com->args && com->args[0])
	{
		execve(com->args[0], com->args, env);
		ft_write(2, "minishell: ");
		ft_write(2, com->args[0]);
		ft_write(2, ":  command not found\n");
		exit(127);
	}
}

void	dir_k(DIR *k)
{
	if (k)
	{
		ft_write(2, "minishell: is directory\n");
		exit(127);
	}
}

void	ft_exech(t_env **all, t_cmd *com, char **env, t_stracto stract)
{
	char	*path;
	DIR		*k;

	if (g_end == 5)
		return (g_end = 0, free(0));
	signal(SIGQUIT, nothing);
	signal(SIGINT, nothing);
	com->pid = fork();
	if (!com->pid)
	{
		if (in_com(com, stract.pips, stract.i) == -1 || in_com(com, stract.pips,
				stract.i) == -2)
			exit(get_exit_status());
		if (out_com(com, stract.pips, stract.n, stract.i) == -1)
			exit(get_exit_status());
		if (stract.a == 2)
			if (!ft_built(all, com))
				exit(get_exit_status());
		k = opendir(com->args[0]);
		dir_k(k);
		path = exe_com(all, com);
		exc2(path, com, env);
		exit(get_exit_status());
	}
}

int	is_built(char *command)
{
	if (!command)
		return (0);
	else if (!ft_strcmp(command, "pwd") || !ft_strcmp(command, "PWD"))
		return (1);
	else if (!ft_strcmp(command, "echo"))
		return (1);
	else if (!ft_strcmp(command, "unset"))
		return (1);
	else if (!ft_strcmp(command, "exit"))
		return (1);
	else if (!ft_strcmp(command, "cd"))
		return (1);
	else if (!ft_strcmp(command, "export"))
		return (1);
	else if (!ft_strcmp(command, "env"))
		return (1);
	else
		return (0);
}
