/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:45 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 03:50:08 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	name_len(char *env)
{
	int	i;

	i = 0;
	while (env[i] != '=' && env[i] != '+' && env[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*name_fun(char *env)
{
	int		i;
	char	*name;

	name = ft_malloc(name_len(env) + 1);
	i = 0;
	while (env[i] != '=' && env[i] != '+' && env[i] != '\0')
	{
		name[i] = env[i];
		i++;
	}
	name[i] = '\0';
	return (name);
}

int	val_len(char *env)
{
	int	i;
	int	j;

	i = name_len(env);
	j = 0;
	while (env[i + j] != '\0')
	{
		j++;
	}
	return (j);
}

void	fill_helper(t_env **all, char *path)
{
	make_node(all, ft_strdup(path), ft_strdup("PWD"), ft_strjoin("PWD=", path));
	make_node(all, ft_strdup("1"), ft_strdup("SHLVL"), ft_strdup("SHLVL=1"));
	make_node(all, ft_strdup("/usr/bin/env"), ft_strdup("_"),
		ft_strdup("_=/usr/bin/env"));
	make_node(all, ft_strdup(""), ft_strdup("OLDPWD"), ft_strdup("OLDPWD"));
	make_node(all,
		ft_strdup("/Users/ojebbari/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/\
						sbin:/usr/local/munki:/Library/Apple/usr/bin:/\
					Users/ojebbari/.brew/bin"),
		ft_strdup("PATH"),
		ft_strdup("OLDPWD=/Users/ojebbari/.brew/bin:/usr/local/bin:/usr/bin:/bin:/usr/sbin:/\
					sbin:/usr/local/munki:/Library/Apple/usr/bin:/\
					Users/ojebbari/.brew/bin"));
}

void	fill_list(t_env **all, char **env)
{
	int		i;
	char	*path;

	i = 0;
	if (*all == NULL && *env == NULL)
	{
		path = getcwd(NULL, 0);
		fill_helper(all, path);
		free(path);
	}
	else if (*all == NULL && *env)
	{
		while (env[i] != NULL)
		{
			make_node(all, val_fun(env[i]), name_fun(env[i]),
				full_line(env[i]));
			i++;
		}
	}
	make_node(all, getcwd(NULL, 0), ft_strdup("h_pwd"), "hiden");
}
