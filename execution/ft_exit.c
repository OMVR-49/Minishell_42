/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:41:11 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:41:11 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	only_digit(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
		{
			if (str[0] != '-')
				return (0);
		}
		i++;
	}
	if (!str[0])
		return (0);
	return (1);
}

void	elsee(char *args)
{
	int				n;
	unsigned char	p;

	n = ft_atoi(args);
	if (n == 2147483647)
	{
		ft_write3(args, "numeric argument required\n");
		set_exit_status(255);
	}
	else
	{
		p = (unsigned char)n;
		set_exit_status(p);
	}
}

void	ft_exit(t_cmd *com)
{
	ft_write(1, "exit\n");
	if (com->args[1] != NULL)
	{
		if (com->args[2] != NULL)
		{
			ft_write(2, "minishell: exit: too many arguments\n");
			set_exit_status(1);
			return ;
		}
		else if (only_digit(com->args[1]) == 0)
		{
			ft_write3(com->args[1], "numeric argument required\n");
			set_exit_status(255);
		}
		else
			elsee(com->args[1]);
	}
	exit(get_exit_status());
}

void	nothing(int sig)
{
	if (sig == SIGQUIT)
	{
		write(1, "Quit: 3\n", 8);
		set_exit_status(131);
	}
	else if (sig == SIGINT)
	{
		write(1, "\n", 1);
		set_exit_status(130);
	}
}
