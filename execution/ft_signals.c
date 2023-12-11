/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:41:23 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:41:25 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	sig_handler(int sig)
{
	if (sig == SIGINT)
	{
		set_exit_status(1);
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handle_exe(int sig)
{
	(void)sig;
	set_exit_status(1);
	rl_on_new_line();
	rl_replace_line("", 0);
	g_end = 10;
	close(0);
}
