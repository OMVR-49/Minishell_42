/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:41:19 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:41:19 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_pwd(t_env **all)
{
	t_env	*tmp;

	tmp = *all;
	while (tmp)
	{
		if (!ft_strcmp(tmp->name, "h_pwd"))
		{
			ft_write(1, tmp->val);
			ft_write(1, "\n");
		}
		tmp = tmp->next;
	}
	set_exit_status(0);
}
