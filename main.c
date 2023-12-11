/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:25:14 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 20:44:55 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(int ac, char **av, char **env)
{
	t_cmd	*head;
	t_env	*all;

	g_end = 0;
	(void) av;
	(void) ac;
	all = NULL;
	head = NULL;
	if (ac == 1)
	{
		set_exit_status(0);
		fill_list(&all, env);
		start_minish(&all, &head);
	}
	return (0);
}
