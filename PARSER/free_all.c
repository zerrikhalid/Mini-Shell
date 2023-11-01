/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_all.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/24 14:22:15 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/31 16:33:04 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_tree(t_tree *tree)
{
	if (!tree)
		return ;
	if (tree->strs[0] && ft_strcmp(tree->strs[0], "<<"))
		unlink(tree->right->strs[0]);
	free_tree(tree->left);
	free_all(tree->strs);
	free_tree(tree->right);
	free(tree);
}

void	free_vars(t_vars *var)
{
	free(var->del);
	free(var->s);
	close(var->fd);
}

void	free_var(char *str)
{
	if (str)
		free(str);
}

void	free_all(char **args)
{
	int	i;

	i = -1;
	while (args && args[++i])
		free(args[i]);
	free(args);
}
