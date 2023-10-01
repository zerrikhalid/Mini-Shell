/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_redir.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/01 14:34:05 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/01 15:35:55 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char **redir(char **strs, int sig)
{
	char	**command;
	int		i;
	int		j;

	i  = -1;
	if (!sig)
	{
		while (strs[++i] && !ft_strchar("<>", strs[i][0]))
			;
		command = (char **)ft_calloc(2, sizeof(char *));
		*command = strs[i];
	}
	else if (sig == 1)
	{
		while (strs[++i] && !ft_strchar("<>", strs[i][0]))
			;
		command = (char **)ft_calloc(2, sizeof(char *));
		*command = strs[i + 1];
	}
	else
	{
		j = -1;
		while (strs[++i] && strs[i][0] != '|')
			;
		command = (char **)ft_calloc(i - 1, sizeof(char *));
		i = -1;
		while (strs[++i] && strs[i][0] != '|')
		{
			if (ft_strchar("<>", strs[i][0]))
				i++;
			else
				command[++j] = strs[i];
		}
	}
	return (command);
}

void	get_redir(t_tree **tree,char **command)
{
	(*tree) = (t_tree *)malloc(sizeof(t_tree));
	(*tree)->strs = redir(command, 0);
	(*tree)->right = (t_tree *)malloc(sizeof(t_tree));
	(*tree)->right->strs = redir(command, 1);
	(*tree)->right->left = NULL;
	(*tree)->right->right = NULL;
	if (ft_strchar("<>", command[0][0]))
	{
		(*tree)->left = (t_tree *)malloc(sizeof(t_tree));
		(*tree)->left->strs = redir(command, 2);
		(*tree)->left->left = NULL;
		(*tree)->left->right = NULL;
	}
}