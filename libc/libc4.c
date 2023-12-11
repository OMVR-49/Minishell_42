/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libc4.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/28 23:45:56 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 20:36:22 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	nlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		return (1);
	if (n < 0)
	{
		n = n * -1;
		i++;
	}
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

char	*ft_itoa(int n)
{
	int		i;
	long	nb;
	char	*p;

	nb = n;
	i = nlen(nb);
	p = ft_malloc(i + 1);
	if (!p)
		return (NULL);
	p[i--] = '\0';
	if (nb == 0)
		p[0] = 48;
	if (nb < 0)
	{
		p[0] = '-';
		nb *= -1;
	}
	while (nb > 0)
	{
		p[i--] = 48 + (nb % 10);
		nb = nb / 10;
	}
	return (p);
}

char	*ft_strdup(const char *s1)
{
	char	*p;
	size_t	len;
	int		i;

	i = 0;
	if (!s1)
		return (ft_strdup(""));
	len = ft_strlen(s1);
	p = ft_malloc(len + 1);
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	p[i] = '\0';
	return (p);
}

size_t	ft_strlen(const char *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (i);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	j;
	char	*p;

	if (!s1)
		return ((char *)s2);
	else if (!s2)
		return ((char *)s1);
	p = (char *)ft_malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	i = 0;
	j = 0;
	while (s1[i])
	{
		p[i] = s1[i];
		i++;
	}
	while (s2[j])
	{
		p[i + j] = s2[j];
		j++;
	}
	p[i + j] = '\0';
	return (p);
}
