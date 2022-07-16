/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ygbouri <ygbouri@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/15 17:34:32 by ygbouri           #+#    #+#             */
/*   Updated: 2022/07/16 17:28:56 by ygbouri          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	exitstatuses(void)
{
	if (WIFEXITED(g_all.status))
		g_all.status_s = WEXITSTATUS(g_all.status);
}

void	execbultincmd(t_tree *root)
{
	int	out;

	out = dup(1);
	if (root->outfile)
		dup2(root->ofd, 1);
	if (ft_strcmp(root->cmd[0], "echo") == 0)
		g_all.status = ft_echo(1, root->cmd);
	else if (ft_strcmp(root->cmd[0], "cd") == 0)
		g_all.status = ft_cd(g_all.env_head, root->cmd[1]);
	else if (ft_strcmp(root->cmd[0], "pwd") == 0)
		g_all.status = ft_pwd();
	else if (ft_strcmp(root->cmd[0], "export") == 0)
		g_all.status = ft_export(root->cmd, g_all.env_head, 0);
	else if (ft_strcmp(root->cmd[0], "unset") == 0)
		g_all.status = ft_unset(&g_all.env_head, root->cmd[1]);
	else if (ft_strcmp(root->cmd[0], "env") == 0)
		g_all.status = ft_env(g_all.env_head);
	else if (ft_strcmp(root->cmd[0], "exit") == 0)
		ft_exit(root->cmd);
	dup2(out, 1);
}

void	execnbultinone(t_tree *root)
{
	if (g_all.lr == -1)
	{
		g_all.pid = fork();
		if (g_all.pid == 0)
		{
			if (root->outfile)
				dup2(root->ofd, 1);
			if (root->infile)
				dup2(root->ifd, 0);
			g_all.root->env = ft_list_to_array();
			execve(g_all.root->path, g_all.root->cmd, g_all.root->env);
			exit(1);
		}
		wait(&g_all.status);
		exitstatuses();
		close(root->ifd);
		close(root->ofd);
	}
}

void	execnbultin(t_tree *root)
{
	if (g_all.lr != -1)
	{
		if (root->outfile)
			dup2(root->ofd, 1);
		if (root->infile)
			dup2(root->ifd, 0);
		g_all.root->env = ft_list_to_array();
		execve(root->path, root->cmd, root->env);
	}
	else
		execnbultinone(root);
}

void	executerpipe(t_tree *root, int p[2], int i)
{
	int		aff;
	int		stdaff;
	t_tree	*cmd;

	aff = 1;
	stdaff = 1;
	cmd = root->left;
	g_all.lr = 1;
	if (i == 1)
	{
		aff = 0;
		stdaff = 0;
		cmd = root->right;
	}
	g_all.pid = fork();
	if (g_all.pid == 0)
	{
		dup2(p[aff], stdaff);
		close(p[0]);
		close(p[1]);
		execmini(cmd);
		exit(1);
	}
}
