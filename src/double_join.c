/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_join.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: momayaz <momayaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:04:18 by momayaz           #+#    #+#             */
/*   Updated: 2022/03/26 16:04:21 by momayaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static void	ft_get_len(char **s1, char **s2, int *i, int *j)
{
	*i = 0;
	*j = 0;
	while (s1[*i])
		(*i)++;
	while (s2[*j])
		(*j)++;
}

static void	ft_gfy_norm(int *i, int *j, int *k)
{
	*i = 0;
	*j = 0;
	*k = 0;
}

static char	*ft_gfy_norm2(char **s1, int *i, int pos)
{
	char	*rst;

	rst = NULL;
	if (*i != pos)
		rst = ft_strdup_garbage(s1[*i]);
	return (rst);
}

char	**ft_double_join(char **s1, char **s2, int pos)
{
	int		i;
	int		j;
	int		k;
	char	**rst;

	ft_get_len(s1, s2, &i, &j);
	rst = (char **)ft_malloc((i + j) * sizeof(char *));
	if (!rst)
		return (NULL);
	ft_gfy_norm(&i, &j, &k);
	while (s1[i])
	{
		rst[k] = ft_gfy_norm2(s1, &i, pos);
		if (i != pos)
			k++;
		i++;
	}
	while (s2[j])
	{
		rst[k] = ft_strdup_garbage(s2[j]);
		k++;
		j++;
	}
	rst[k] = 0;
	return (rst);
}
