/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/08 17:26:20 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 03:57:11 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strncpy(char *src, char *dest, int n)
{
	int	i;

	i = 0;
	while (src[i] && i <= n)
	{
		dest[i] = src[i];
		i++;
	}
	while (i <= n)
		dest[i++] = '\0';
	return (dest);
}

int	ft_iswspace(char c)
{
	if (c == ' ' || c == '\t' || c == '\v' || c == '\r' || c == '\f'
		|| c == '\n')
		return (1);
	return (0);
}

int	ft_striswspace(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (!ft_iswspace(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ft_is_special(char c)
{
	if (c == '<' || c == '>' || c == '|' || c == '\'' || c == '\"'
		|| (ft_iswspace(c)) || c == '\n' || c == '\0')
		return (1);
	else
		return (0);
}

int	ft_readline(char **l)
{
	*l = readline("[minishell]$ ");
	ft_lstadd_back_clctr(ft_garbege_collector(), ft_lstnew_clctr(*l));
	if (!*l)
	{
		printf("exit\n");
		exit(0);
	}
	if (ft_strncmp(*l, "", 1) == 0 || ft_striswspace(*l))
		return (1);
	if (ft_strlen(*l) > 0)
		add_history(ft_strdup(*l));
	return (0);
}
