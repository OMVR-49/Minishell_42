/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: eoussama <eoussama@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/02 02:09:32 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 03:00:21 by eoussama         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	zeero(int *i, int *t, int *start, int *inquotes)
{
	*i = 0;
	*t = 0;
	*start = 0;
	inquotes = 0;
}

void	ft_ext(int i)
{
	if (i == 1)
		printf("ft_malloc fails\n");
	exit(1);
}

int	ft_exit_status(int i, int status)
{
	static int	j;

	if (status)
		j = i;
	return (j);
}

int	get_exit_status(void)
{
	return (ft_exit_status(49, 0));
}

void	set_exit_status(int i)
{
	ft_exit_status(i, 1);
}
