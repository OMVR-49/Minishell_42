/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exe.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:39:56 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:39:56 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	close_in_out(int sin, int sout)
{
	dup2(sin, 0);
	dup2(sout, 1);
	close(sin);
	close(sout);
}

void	one_cmd(t_cmd *com, t_env **all, int **pips, char **env)
{
	int			sin;
	int			sout;
	int			n;
	t_stracto	stract;

	stract.pips = pips;
	stract.i = 0;
	stract.a = 1;
	stract.n = pip_num(com);
	sin = dup(0);
	sout = dup(1);
	stract.i = 0;
	n = pip_num(com);
	if (com->args && is_built(com->args[0]))
	{
		if (in_com(com, pips, stract.i) != -1)
		{
			out_com(com, pips, n, stract.i);
			ft_built(all, com);
		}
	}
	else
		ft_exech(all, com, env, stract);
	close_in_out(sin, sout);
}

void	multi_cmd(t_cmd *com, t_env **all, int **pips, char **env)
{
	int			sin;
	int			sout;
	t_stracto	stract;

	stract.pips = pips;
	stract.i = 0;
	stract.a = 2;
	stract.n = pip_num(com);
	sin = dup(0);
	sout = dup(1);
	while (com)
	{
		if (stract.i < (stract.n - 1))
			pipe(pips[stract.i]);
		ft_exech(all, com, env, stract);
		if (stract.i >= 1)
		{
			close(pips[stract.i - 1][0]);
			close(pips[stract.i - 1][1]);
		}
		stract.i++;
		com = com->next;
	}
	close(sout);
	close(sin);
}

int	ft_exe(t_env **all, t_cmd *com)
{
	int		**pips;
	t_cmd	*tmp;
	t_cmd	*tmp3;
	int		n;

	n = pip_num(com);
	pips = alloc_pipes(n);
	tmp = com;
	tmp3 = com;
	here_beg(com, all);
	if (n == 1)
		one_cmd(com, all, pips, env_to_char(*all));
	else
		multi_cmd(com, all, pips, env_to_char(*all));
	return (wait_all(pips, tmp, tmp3, n));
}
