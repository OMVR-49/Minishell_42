/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:41:05 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:41:05 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env **all, t_cmd *com)
{
	t_env	*tmp;

	tmp = *all;
	if (com->args && com->args[1] != NULL)
	{
		ft_write(2, "env: ");
		ft_write(2, com->args[1]);
		ft_write(2, ": No such file or directory\n");
		set_exit_status(1);
		return (1);
	}
	while (tmp != NULL)
	{
		if (ft_strcmp(tmp->name, "h_pwd") != 0)
		{
			if (ft_strchr(tmp->line, '='))
			{
				printf("%s=%s\n", tmp->name, tmp->val);
			}
		}
		tmp = tmp->next;
	}
	set_exit_status(0);
	return (0);
}
