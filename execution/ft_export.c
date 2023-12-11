/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:39:34 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:39:34 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	add_item(t_env **all, char *str, int v)
{
	t_env	*tmp;
	char	*name;
	char	*val;
	int		x;

	x = 0;
	tmp = *all;
	name = name_fun(str);
	while (tmp)
	{
		if (ft_strcmp(name, tmp->name) == 0)
		{
			x++;
			val = val_fun(str);
			if (!val)
				return ;
			add_helper(tmp, str, val, v);
		}
		tmp = tmp->next;
	}
	if (x == 0)
		make_node(all, val_fun(str), name, str);
}

int	valid_name(char *str)
{
	int	i;

	i = 1;
	while (str[i] != '=' && str[i] != '\0')
	{
		if (ft_isalnum(str[i]) == 0 && str[i] != '_')
		{
			if (str[i] == '+' && str[i + 1] == '=')
				return (i + 1);
			return (0);
		}
		i++;
	}
	return (1);
}

int	beg(char c)
{
	if (c == '_' || ft_isalpha(c))
	{
		return (1);
	}
	else
	{
		return (0);
	}
}

void	add_to_list(t_env **all, t_cmd *com)
{
	int	i;
	int	v;

	i = 1;
	while (com->args[i])
	{
		v = valid_name(com->args[i]);
		if (beg(com->args[i][0]) && v)
		{
			add_item(all, com->args[i], v);
			set_exit_status(0);
		}
		else
		{
			ft_write(2, "bash: export: `");
			ft_write(2, com->args[i]);
			ft_write(2, "': not a valid identifier\n");
			set_exit_status(1);
		}
		i++;
	}
}

int	ft_export(t_env **all, t_cmd *com)
{
	t_env	*tmp;

	tmp = NULL;
	if (!com->args[1])
	{
		copy_list(all, &tmp);
		sort_list(&tmp);
		print_list(tmp);
		free_list(tmp);
		set_exit_status(0);
	}
	else if (com->args[1])
	{
		add_to_list(all, com);
	}
	return (0);
}
