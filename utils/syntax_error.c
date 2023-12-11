/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/26 04:07:44 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 17:34:06 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	syntax_errors_return_status(int x)
{
	if (x == 1)
	{
		ft_write(2, "minishell: command not found\n");
	}
	else if (x == 2)
	{
		ft_write(2, "minishell: syntax error\n");
		set_exit_status(258);
	}
	else if (x == 3)
		ft_write(2,
			"minishell: syntax error near unexpected token`newline'\n");
	else if (x == 4)
		ft_write(2, "minishell: syntax error near unexpected token `|'\n");
}

int	syntax_error(t_anelement *head)
{
	while (head != NULL)
	{
		if (head->tk == RDR_IN || head->tk == RDR_OUT || head->tk == APPEND
			|| head->tk == HERE_DOC)
		{
			if (!head->next)
				return (set_exit_status(258), 3);
			else if ((head->next->tk != WORD) && (head->next->tk != ENV))
				return (set_exit_status(258), 3);
		}
		else if (head->tk == _PIPE)
		{
			if (!head->next || !head->prev)
				return (set_exit_status(258), 4);
		}
		head = head->next;
	}
	return (0);
}
