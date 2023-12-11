/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/27 01:54:28 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 20:21:35 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	ft_left(char const *str0, char const *set0)
{
	int	i;
	int	j;

	i = -1;
	j = 0;
	while (set0[++i] != '\0')
	{
		if (set0[i] == str0[j])
		{
			j++;
			i = -1;
		}
	}
	return (j);
}

static int	ft_right(char const *str1, char const *set1)
{
	int	i;
	int	j;

	i = -1;
	j = ft_strlen(str1) - 1;
	while (set1[++i] != '\0')
	{
		if (set1[i] == str1[j] && j >= 0)
		{
			j--;
			i = -1;
		}
	}
	j++;
	return (j);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	i;
	unsigned int	j;
	char			*p;

	if (!*s1 || !set)
		return (ft_strdup(s1));
	i = ft_left(s1, set);
	j = ft_right(s1, set);
	if (i == (j - i))
	{
		p = ft_strdup("");
		if (!p)
			return (0);
		else
			return (p);
	}
	p = ft_substr(s1, i, (j - i));
	return (p);
}

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n && (s1[i] != '\0' || s2[i] != '\0'))
	{
		if (s1[i] != s2[i])
		{
			return ((unsigned char)s1[i] - (unsigned char)s2[i]);
		}
		i++;
	}
	return (0);
}

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count == SIZE_MAX || size == SIZE_MAX)
		return (0);
	p = ft_malloc(count * size);
	if (!p)
		return (NULL);
	ft_bzero(p, size * count);
	return (p);
}
