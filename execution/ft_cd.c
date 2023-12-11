/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:52 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:40:52 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_swap(t_env *cur, t_env *next)
{
	char	*t_name;
	char	*t_val;
	char	*t_line;

	t_name = cur->name;
	t_val = cur->val;
	t_line = cur->line;
	cur->name = next->name;
	cur->val = next->val;
	cur->line = next->line;
	next->name = t_name;
	next->val = t_val;
	next->line = t_line;
}

void	sort_list(t_env **exp)
{
	t_env	*cur;
	t_env	*next;

	cur = *exp;
	while (cur != NULL)
	{
		next = cur->next;
		while (next != NULL)
		{
			if (ft_strcmp(cur->name, next->name) > 0)
			{
				ft_swap(cur, next);
			}
			next = next->next;
		}
		cur = cur->next;
	}
}

void	ft_replace(t_env **all, char *arg, char *name, int x)
{
	t_env	*tmp;
	int		i;

	tmp = *all;
	i = 1;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, name))
		{
			i--;
			free(tmp->val);
			tmp->val = ft_strdup(arg);
		}
		tmp = tmp->next;
	}
	if (x && i)
	{
		make_node(all, ft_strdup(arg), ft_strdup("OLDPWD"), ft_strjoin("OLDPWD",
				arg));
	}
	set_exit_status(0);
}

void	cd_help(char *str, char *opath)
{
	ft_write3(str, ": No such file or directory\n");
	free(opath);
	set_exit_status(1);
}

void	ft_cd(t_env **all, t_cmd *com)
{
	char	*opath;
	char	*cpath;

	opath = getcwd(NULL, 0);
	if (com->args && com->args[1])
	{
		if (chdir(com->args[1]) == 0)
		{
			cpath = getcwd(NULL, 0);
			if (cpath == NULL)
			{
				ft_write(2, "minishell: cd error\n");
				return ;
			}
			ft_replace(all, cpath, "h_pwd", 0);
			ft_replace(all, cpath, "PWD", 0);
			ft_replace(all, opath, "OLDPWD", 1);
			free(cpath);
			free(opath);
		}
		else
			cd_help(com->args[1], opath);
	}
	else
		free(opath);
}
