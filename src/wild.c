/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wild.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 22:52:43 by ygbouri           #+#    #+#             */
/*   Updated: 2022/07/16 18:14:41 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_export_mini_mini(char **str, t_env *head)
{
	if (!str[1])
	{
		ft_affiche_export(head);
		return (0);
	}
	g_all.exi = 0;
	g_all.exk = -1;
	return (1);
}

char	**etoile(t_wild wi)
{
	wi.dir = opendir(".");
	if (wi.dir == NULL)
		return (0);
	wi.i = 0;
	wi.wild = readdir(wi.dir);
	while (wi.wild)
	{
		wi.i++;
		wi.wild = readdir(wi.dir);
	}
	wi.t = (char **)malloc(wi.i * sizeof(char *) + 1);
	closedir(wi.dir);
	wi.dir = opendir(".");
	wi.wild = readdir(wi.dir);
	wi.i = 0;
	while (wi.wild)
	{
		wi.t[wi.i] = ft_strdup(wi.wild->d_name);
		wi.i++;
		wi.wild = readdir(wi.dir);
	}
	wi.t[wi.i] = NULL;
	closedir(wi.dir);
	return (wi.t);
}
