/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:05:37 by momayaz           #+#    #+#             */
/*   Updated: 2022/03/26 16:05:39 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static int	str_len(const char *s, char c)
{
	int	i;

	i = 0;
	while (*s && (*s++ != c))
		i++;
	return (i);
}

static int	count_world(const char *s, char c)
{
	int	i;
	int	j;

	j = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		i = str_len(s, c);
		s += i;
		if (i)
			j++;
	}
	return (j);
}

static char	*str_cpy(const char *s, int size)
{
	char	*t;

	t = malloc((size + 1) * sizeof(char));
	if (!t)
		return (0);
	t[size] = 0;
	while (size--)
		t[size] = s[size];
	return (t);
}

char	**ft_split(char *s, char c)
{
	char	**t;
	int		size;
	int		n;
	int		i;

	if (!s)
		return (NULL);
	size = count_world(s, c);
	t = malloc ((size + 1) * sizeof(char *));
	if (!t)
		return (0);
	i = -1;
	while (++i < size)
	{
		while (*s && *s == c)
			s++;
		n = str_len(s, c);
		t[i] = str_cpy(s, n);
		if (!(t[i]))
			return (free_tab(t), NULL);
		s += n;
	}
	t[size] = 0;
	return (t);
}
