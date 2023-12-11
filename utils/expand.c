/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/20 10:41:52 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 01:49:06 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	get_key_len(char *key)
{
	int	i;

	i = 0;
	if (*key == '?')
		return (1);
	while (key[i] && (ft_isalpha(key[i]) || key[i] == '_'))
		i++;
	return (i);
}

char	*expand_all(char *lmo7tawa, char *pp, t_env **all, int *i)
{
	char	*env_val;
	char	*tmp;
	int		key_len;

	if (*pp == '?')
	{
		env_val = ft_itoa(get_exit_status());
		*i += 1;
	}
	else
	{
		key_len = get_key_len(pp);
		*i += key_len;
		env_val = find_name(all, pp, key_len);
	}
	if (lmo7tawa && !*lmo7tawa && !env_val)
		return (NULL);
	tmp = ft_strjoin(lmo7tawa, env_val);
	return (tmp);
}

int	check_valid_env(char *s, t_anelement *elem)
{
	if (elem->prev && elem->prev->tk == HERE_DOC)
		return (0);
	if (ft_isalpha(*s) || *s == '_' || *s == '?')
		return (1);
	return (0);
}

char	*handler(t_anelement *head, t_env **all)
{
	char		*lmo7tawa;
	char		*l;
	int			i;
	int			j;

	i = 0;
	j = 0;
	l = head->content;
	lmo7tawa = ft_strdup("");
	while (l[i])
	{
		if (l[i] == '\'' && j != 2)
			cn(1, &j);
		else if (l[i] == '\"' && j != 1)
			cn(2, &j);
		else if (l[i] == '$' && check_valid_env(l + i + 1, head) && j != 1)
			lmo7tawa = expand_all(lmo7tawa, l + i + 1, all, &i);
		else
			lmo7tawa = join_one(lmo7tawa, l[i]);
		i++;
	}
	head->tk = WORD;
	return (lmo7tawa);
}
