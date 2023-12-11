/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:41:30 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:41:30 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*val_fun(char *env)
{
	char	*val;
	int		i;
	int		j;

	if (!ft_strchr(env, '='))
		return (NULL);
	val = ft_malloc(val_len(env) + 1);
	i = name_len(env) + 1;
	if (env[i - 1] != '=' && env[i - 1] != '\0')
		i++;
	j = 0;
	while (env[i + j] != '\0')
	{
		val[j] = env[i + j];
		j++;
	}
	val[j] = '\0';
	return (val);
}

void	check_del(t_env **all, char *name)
{
	t_env	*cur;
	t_env	*tmp;

	cur = *all;
	if (!ft_strcmp(cur->name, name))
	{
		*all = cur->next;
		free(cur);
	}
	else
	{
		while (cur->next)
		{
			if (!ft_strcmp(cur->next->name, name))
			{
				tmp = cur->next;
				cur->next = cur->next->next;
				free(tmp);
				break ;
			}
			cur = cur->next;
		}
	}
}

void	ft_unset(t_env **all, t_cmd *com)
{
	int	i;
	int	v;

	i = 1;
	while (com->args && com->args[i])
	{
		v = valid_name(com->args[i]);
		if (beg(com->args[i][0]) && v)
		{
			check_del(all, com->args[i]);
			set_exit_status(0);
		}
		else
		{
			ft_write(2, "minishell: unset: `");
			ft_write(2, com->args[i]);
			ft_write(2, "': not a valid identifier\n");
			set_exit_status(1);
		}
		i++;
	}
}
