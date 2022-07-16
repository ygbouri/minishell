/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:03:57 by momayaz           #+#    #+#             */
/*   Updated: 2022/06/23 10:39:16 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_env(t_env *lst)
{
	if (!lst)
		return (1);
	while (lst)
	{
		if (lst->value)
			printf("%s=%s\n", lst->key, lst->value);
		lst = lst->next;
	}
	return (0);
}

int	ft_pwd(void)
{
	char	path[2000];

	getcwd(path, 2000);
	printf("%s\n", path);
	return (0);
}

int	ft_echo(int index, char **s)
{
	int	i;

	i = 0;
	while (s[index] && !ft_strcmp(s[index], "-n"))
	{
		index++;
		i++;
	}
	while (s[index])
	{
		printf("%s", s[index++]);
		if (s[index])
			printf(" ");
	}
	if (!i)
		printf("\n");
	return (0);
}

static int	ft_cd_mini(t_env *env, char *path)
{
	char	*home;

	home = ft_get_env(env, "HOME");
	printf("home : %s\n", home);
	if (!home)
	{
		write(2, "MiniShell: cd: HOME not set\n", 28);
		return (1);
	}
	ft_edit_env(env, "OLDPWD", path);
	chdir(home);
	getcwd(path, 2000);
	ft_edit_env(env, "PWD", path);
	return (0);
}

int	ft_cd(t_env *env, char *s)
{
	char	path[2000];

	getcwd(path, 2000);
	if (!s || !ft_strcmp("~", s))
		return (ft_cd_mini(env, path));
	if (s[0] != '/' && s[0] != '.')
		ft_strjoin2("./", s);
	if (!access(s, F_OK))
	{
		ft_edit_env(env, "OLDPWD", path);
		chdir(s);
		getcwd(path, 2000);
		ft_edit_env(env, "PWD", path);
		return (0);
	}
	else
	{
		printf("%s: not found\n", s);
		return (1);
	}
}
