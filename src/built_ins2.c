/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   built_ins2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/26 16:04:01 by momayaz           #+#    #+#             */
/*   Updated: 2022/07/16 18:29:03 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	ft_unset_mini(char *str, int *i)
{
	while (str[*i])
	{
		if (!ft_isalnum(str[*i]))
		{
			printf("unset `%s' : not a valid identifier\n", str);
			return (1);
		}
		(*i)++;
	}
	return (0);
}

int	ft_unset(t_env **lst, char *str)
{
	int		i;
	t_env	*tmp_env;
	t_env	*tmp_env2;

	i = 0;
	if (!str)
		return (0);
	if (ft_unset_mini(str, &i))
		return (1);
	tmp_env = lst[0];
	while (tmp_env)
	{
		if (tmp_env->next && !ft_strcmp(tmp_env->next->key, str))
		{
			tmp_env2 = tmp_env->next;
			tmp_env->next = tmp_env2->next;
			free(tmp_env2->key);
			free(tmp_env2->value);
			free(tmp_env2);
			return (0);
		}
		tmp_env = tmp_env->next;
	}
	return (1);
}

void	ft_affiche_export(t_env *head)
{
	if (!head)
		return ;
	while (head)
	{
		printf("declare -x ");
		printf("%s", head->key);
		if (head->value)
			printf("=\"%s\"", head->value);
		printf("\n");
		head = head->next;
	}
}

int	ft_export_mini(t_env *head, char *str, int i)
{
	char	*str1;
	char	*str2;

	if (!ft_isalnum(str[i]))
	{
		if (i == 0 || str[i] != '=')
		{
			ft_print_error("MiniShell: export: `", str + i, \
			"': not a valid identifier\n");
			return (1);
		}
		if (str[i] == '=')
		{
			str1 = ft_substr(str, 0, i);
			str2 = ft_substr(str, i + 1, ft_strlen(str));
			ft_edit_env(head, str1, str2);
			free(str1);
			free(str2);
			return (0);
		}
	}
	return (-1);
}

int	ft_export(char **str, t_env *head, int cp)
{
	if (ft_export_mini_mini(str, head) == 0)
		return (0);
	while (str[++g_all.exi])
	{
		g_all.exk = -1;
		while (str[g_all.exi][++g_all.exk])
		{
			if (ft_isalpha(str[g_all.exi][g_all.exk]))
				cp++;
			if (str[g_all.exi][g_all.exk] > '0'
				&& str[g_all.exi][g_all.exk] < '9' && !cp)
			{
				ft_print_error("MiniShell: export: `", str[g_all.exi], \
				"': not a valid identifier\n");
				return (1);
			}
			g_all.exj = ft_export_mini(head, str[g_all.exi], g_all.exk);
			if (g_all.exj != -1)
			{
				break ;
			}
		}
		ft_edit_env(head, str[g_all.exi], NULL);
	}
	return (0);
}
