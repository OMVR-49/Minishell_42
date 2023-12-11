/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:40:57 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:40:57 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_write(int fd, char *str)
{
	write(fd, str, ft_strlen(str));
}

int	just_n(char *str, int ind)
{
	while (str[ind] != '\0')
	{
		if (str[ind] != 'n')
		{
			return (0);
		}
		ind++;
	}
	return (1);
}

int	is_line(char **str)
{
	int	ind;

	ind = 1;
	if (str == NULL || str[ind] == NULL)
		return (1);
	while (str[ind] && str[ind][0] == '-' && str[ind][1] == 'n'
		&& just_n(str[ind], 2))
	{
		ind++;
	}
	return (ind);
}

void	ft_echo(t_cmd *com)
{
	char	**ar;
	int		l;
	int		ind;

	ar = com->args;
	l = is_line(ar);
	ind = l;
	while (ar[ind] != NULL)
	{
		write(1, ar[ind], ft_strlen(ar[ind]));
		if (ar[ind + 1])
			write(1, " ", 1);
		ind++;
	}
	if (l == 1)
	{
		write(1, "\n", 1);
	}
}
