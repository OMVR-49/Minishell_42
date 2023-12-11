/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:25:37 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 03:48:12 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	sigg(int *h)
{
	signal(SIGINT, &sig_handler);
	signal(SIGQUIT, SIG_IGN);
	dup2((*h), 0);
}

void	ft_exe2(t_env **all, t_cmd *data)
{
	signal(SIGINT, &handle_exe);
	signal(SIGQUIT, SIG_IGN);
	ft_exe(all, data);
}

void	start_minish(t_env **all, t_cmd **data)
{
	char		*l;
	int			h;

	l = NULL;
	h = dup(0);
	rl_catch_signals = 0;
	while (1)
	{
		sigg(&h);
		if (ft_readline(&l))
			continue ;
		if (checking_quotes(l))
			syntax_errors_return_status(2);
		else
		{
			(*data) = parser(l, all);
			if ((*data))
				ft_exe2(all, *data);
		}
	}
	return ;
}
