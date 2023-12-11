/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_here_doc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 01:25:01 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:54:18 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_count(char *l)
{
	int	i;

	i = 0;
	while (l[i] && l[i] != '$')
		i++;
	return (i);
}

int	check_valid_env_rsb(char *s)
{
	if (*s && (ft_isalpha(*s) || *s == '_' || *s == '?'))
		return (1);
	return (0);
}

char	*expand_heredoc(char *line, t_env **all)
{
	t_heredoc		b;

	b.i = 0;
	b.result = NULL;
	while (line[b.i] != '\0')
	{
		if (line[b.i] == '$' && check_valid_env_rsb(line + b.i + 1))
		{
			b.env_n_l = get_key_len(line + ++b.i);
			b.env_val = find_name(all, line + b.i, b.env_n_l);
			b.result = ft_strjoin(b.result, b.env_val);
			b.i += b.env_n_l;
		}
		else if (line[b.i] == '$')
			b.result = ft_strjoin(b.result, ft_strdup("$")) + ++b.i * 0;
		else
		{
			b.s = ft_substr(line + b.i, 0, ft_count(line + b.i));
			b.result = ft_strjoin(b.result, b.s);
			b.i += ft_count(line + b.i);
		}
	}
	if (!b.result)
		return (ft_strdup(""));
	return (b.result);
}
