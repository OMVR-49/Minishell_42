/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc2.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 20:34:54 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/09 02:36:30 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_strchr(const char *str, int c)
{
	int		i;
	char	*s;

	i = 0;
	s = (char *)str;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return (&s[i]);
		i++;
	}
	if (s[i] == (char)c)
		return (&s[i]);
	return (0);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	size_t	i;

	i = 0;
	while ((s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	passage_per_address(size_t *i, size_t *j, int start)
{
	*i = start;
	*j = 0;
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s)
		return (0);
	if (start >= ft_strlen(s))
		return (ft_strdup(""));
	if (ft_strlen(s) < len)
		len = ft_strlen(s) - start;
	p = (char *)ft_malloc(len + 1);
	if (!p)
		return (0);
	passage_per_address(&i, &j, start);
	while (s[i] != '\0')
	{
		if (i < (len + start))
		{
			p[j++] = s[i];
		}
		i++;
	}
	p[j] = '\0';
	return (p);
}
