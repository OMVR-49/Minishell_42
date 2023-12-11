/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe1.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:03 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 02:32:56 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	num_d(char **here)
{
	int	i;

	i = 0;
	while (here[i])
	{
		i++;
	}
	return (i);
}

t_env	*ft_search(t_env **all, char *name)
{
	t_env	*tmp;

	tmp = *all;
	while (tmp)
	{
		if (ft_strcmp(tmp->name, name) == 0)
		{
			return (tmp);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*exe_com(t_env **all, t_cmd *com)
{
	t_env	*f_path;
	char	*comd;
	char	**paths;
	char	*tmp;
	int		i;

	if (!com->args[0])
		return (NULL);
	f_path = ft_search(all, "PATH");
	if (f_path != NULL)
	{
		if (com->args[0] && (com->args[0][0] == '.' || com->args[0][0] == '/'))
			return (ft_strdup(com->args[0]));
		comd = ft_strjoin("/", com->args[0]);
		paths = ft_split(f_path->val, ':');
		i = 0;
		while (paths && paths[i])
		{
			tmp = ft_strjoin(paths[i], comd);
			if (access(tmp, X_OK) != -1)
				return (tmp);
			i++;
		}
	}
	return (NULL);
}

int	ft_built(t_env **all, t_cmd *com)
{
	if (!com || !com->args[0])
		return (1);
	else if (!ft_strcmp(com->args[0], "pwd") || !ft_strcmp(com->args[0], "PWD"))
		return (ft_pwd(all), 0);
	else if (!ft_strcmp(com->args[0], "echo"))
		return (ft_echo(com), 0);
	else if (!ft_strcmp(com->args[0], "unset"))
		return (ft_unset(all, com), 0);
	else if (!ft_strcmp(com->args[0], "exit"))
		return (ft_exit(com), 0);
	else if (!ft_strcmp(com->args[0], "cd"))
		return (ft_cd(all, com), 0);
	else if (!ft_strcmp(com->args[0], "export"))
		return (ft_export(all, com), 0);
	else if (!ft_strcmp(com->args[0], "env"))
		return (ft_env(all, com), 0);
	else
		return (1);
}

int	pip_num(t_cmd *com)
{
	t_cmd	*tmp;
	int		i;

	tmp = com;
	i = 0;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}
