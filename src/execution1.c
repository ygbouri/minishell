/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/16 17:23:09 by ygbouri           #+#    #+#             */
/*   Updated: 2022/07/16 17:30:54 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	checkdollar(char **str)
{
	int	i;

	i = 1;
	while (str[i])
	{
		if (str[i][0] == '$')
			str[i] = ft_parse_dollar(str[i], 0);
		i++;
	}
}

void	execmini(t_tree *root)
{
	if (root->token == COMMAND)
	{
		checkdollar(root->cmd);
		if (root->is_builtin == 1)
			execbultincmd(root);
		else if (root->is_builtin == 0)
			execnbultin(root);
	}
	else if (root->token == PIPE)
	{
		execpipe(root);
	}
	else if (root->token == AND)
	{
		execmini(root->left);
		if (g_all.status_s == 0)
			execmini(root->right);
	}
	else if (root->token == OR)
	{
		execmini(root->left);
		if (g_all.status_s != 0)
			execmini(root->right);
	}
}

void	handc(int sig)
{
	(void)sig;
	if (g_all.status_s == 0)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	handlerback(int sig)
{
	(void)sig;
	if (g_all.status_s == 0)
	{
		rl_redisplay();
		return ;
	}
}

void	execpipe(t_tree *root)
{
	g_all.i = pipe(root->p);
	executerpipe(root, root->p, 0);
	executerpipe(root, root->p, 1);
	close(root->p[0]);
	close(root->p[1]);
	wait(&g_all.status);
	exitstatuses();
	wait(&g_all.status);
	exitstatuses();
	close(root->ifd);
	close(root->ofd);
}
