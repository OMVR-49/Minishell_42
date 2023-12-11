/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:38 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 02:35:40 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	copy_list(t_env **all, t_env **tmp)
{
	t_env	*sort;

	sort = *all;
	while (sort != NULL)
	{
		make_node(tmp, ft_strdup(sort->val), ft_strdup(sort->name),
			ft_strdup(sort->line));
		sort = sort->next;
	}
}

char	*find_name(t_env **all, char *key, int keylen)
{
	t_env	*tmp;

	tmp = *all;
	if (*key == '?')
		return (ft_itoa(get_exit_status()));
	while (tmp)
	{
		if (!ft_strncmp(tmp->name, key, keylen) && !tmp->name[keylen])
			return (tmp->val);
		tmp = tmp->next;
	}
	return (NULL);
}

void	print_list(t_env *tmp)
{
	t_env	*print;

	print = tmp;
	while (print != NULL)
	{
		if (ft_strcmp(print->name, "h_pwd") != 0)
		{
			ft_write(1, "declare -x ");
			ft_write(1, print->name);
			if (ft_strchr(print->line, '='))
			{
				ft_write(1, "=");
				ft_write(1, "\"");
				if (print->val && print->val[0] != '\0')
					ft_write(1, print->val);
				ft_write(1, "\"");
			}
			ft_write(1, "\n");
		}
		print = print->next;
	}
}

void	free_list(t_env *tmp)
{
	t_env	*frr;

	frr = tmp;
	while (tmp != NULL)
	{
		frr = tmp;
		tmp = tmp->next;
		free(frr);
	}
}

void	add_helper(t_env *tmp, char *str, char *val, int v)
{
	char	*frr;

	frr = tmp->val;
	if (v > 1)
		tmp->val = ft_strjoin(frr, val);
	else
		tmp->val = val;
	free(tmp->line);
	free(frr);
	tmp->line = str;
}
