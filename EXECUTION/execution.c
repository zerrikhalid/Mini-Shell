/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execution.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/05 14:20:38 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/19 15:34:14 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_all(char **args)
{
	int	i;

	i = -1;
	while (args[++i])
		free(args[i]);
	free(args);
}

void	cmd_execute(t_tree *tree, t_data *envi, char **env)
{
	int	i;

	i = -1;
	if (!fork())
	{
		while (!tree->strs[++i] && i < tree->count)
			;
		if (ft_strchar(tree->strs[i], '/'))
			tree->strs[i] = get_cmd(tree->strs[i], envi);
		if (execve(tree->strs[i], &tree->strs[i], env) == -1)
			puts(strerror(errno));
		exit(1);
	}
	wait(0);
}

void	check_builtin(t_tree *tree, t_data *envi, char **environement)
{
	if (tree->strs[0] && ft_strcmp(tree->strs[0], "echo"))
		g_status = echo(&tree->strs[1]);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "cd"))
		g_status = cd(tree->strs[1], &envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "pwd"))
		g_status = pwd();
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "export"))
		g_status = export(tree->strs, &envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "unset"))
		g_status = unset(tree->strs, &envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "env"))
		g_status = env(envi);
	else if (tree->strs[0] && ft_strcmp(tree->strs[0], "exit"))
		g_status = ft_exit(&tree->strs[1]);
	else
		cmd_execute(tree, envi, environement);
}

void	execute(t_tree *tree, t_data *env, char **environement)
{
	if (ft_strcmp(tree->strs[0], "|"))
		ft_pipe(tree, env, environement);
	else if (ft_strcmp(tree->strs[0], "<"))
		ft_left_red(tree, env, environement);
	else if (ft_strcmp(tree->strs[0], ">"))
		ft_right_red(tree, env, environement);
	else if (ft_strcmp(tree->strs[0], "<<"))
		ft_l_double_red(tree, env, environement);
	else if (ft_strcmp(tree->strs[0], ">>"))
		ft_r_double_red(tree, env, environement);
	else
		expand(tree, env, environement);
}
