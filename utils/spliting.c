/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   spliting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ojebbari <ojebbari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 02:45:38 by ojebbari          #+#    #+#             */
/*   Updated: 2023/12/08 12:45:12 by ojebbari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	quote_state(char c, int *inquotes)
{
	if (c == '\'' && *inquotes == 1)
		*inquotes = 0;
	else if (c == '\"' && *inquotes == 2)
		*inquotes = 0;
	else if (c == '\'' && *inquotes == 0)
		*inquotes = 1;
	else if (c == '\"' && *inquotes == 0)
		*inquotes = 2;
}

int	wordc(char const *s)
{
	int	inquotes;
	int	i;
	int	x;

	i = 0;
	x = 0;
	inquotes = 0;
	while (s[i])
	{
		while (ft_iswspace(s[i]))
			i++;
		if (s[i] && inquotes == 0)
			x++;
		while ((!ft_iswspace(s[i]) && s[i]) || inquotes)
		{
			quote_state(s[i], &inquotes);
			i++;
		}
	}
	return (x);
}

static char	*wordp(const char *s, int st, int en)
{
	char	*p;
	int		x;

	x = 0;
	p = ft_malloc((en - st + 1) * sizeof(char));
	while (st < en)
		p[x++] = s[st++];
	p[x] = '\0';
	return (p);
}

char	**ft_split2(char *s)
{
	static int	inquotes;
	int			start;
	char		**str;
	int			i;
	int			j;

	zeero(&i, &j, &start, &inquotes);
	if (!s)
		ft_ext(1);
	str = (char **)ft_malloc(sizeof(char *) * (wordc(s) + 2));
	quote_state(s[j], &inquotes);
	if (inquotes)
		j++;
	while (s[j])
	{
		while (s[j] && (!ft_iswspace(s[j]) || inquotes))
			quote_state(s[j++], &inquotes);
		if (j > start)
			str[i++] = wordp(s, start, j);
		while (ft_iswspace(s[j]) && !inquotes)
			quote_state(s[j++], &inquotes);
		start = j;
	}
	return (str[i] = NULL, str);
}
