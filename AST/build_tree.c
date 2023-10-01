// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   build_tree.c                                       :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2023/09/26 17:16:17 by kzerri            #+#    #+#             */
// /*   Updated: 2023/09/28 14:26:49 by kzerri           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

#include "../minishell.h"

int search_pipe(char **strs, int index)
{
	int	i;

	i = index - 1;
	while (strs[++i])
	{
		if (ft_strcmp(strs[i], "|"))
			return (i);
	}
	return (0);
}

int	search_redicrection(char **strs)
{
	int	i;

	i = -1;
	while (strs[++i] && strs[i][0] != '|')
	{
		if (!ft_strchar("<>", strs[i][0]))
			return (i);
	}
	return (-1);
}

char **pipe_command(char **strs, int sig, char *s)
{
	char	**res;
	int		len;
	int		i;

	len = ft_strlen(s);
	if (sig == 0)
	{
		res = (char **)calloc(len + 1, sizeof(char *));
		res[0] = s;
	}
	else
	{
		i = -1;
		while (strs[len] && strs[len][0] != '|')
			len++;
		res = (char **)calloc(len + 1, sizeof(char *));
		while (++i < len)
			res[i] = strs[i];
	}
	return (res);
}

t_tree *create(char **strs)
{
	t_tree	*tree;

	tree = (t_tree *)malloc(sizeof(t_tree));
	tree->strs = strs;
	tree->left = NULL;
	tree->right = NULL;
	return (tree);
}

void	get_tree(t_tree **tree, char **command, int sig)
{
	if (!(*tree) && !sig)
	{
			*tree = create(command);
		return ;
	}
	else if (ft_strcmp(command[0], "|"))
		get_tree(&(*tree)->right, command, sig);
	else if (sig == 1)
	{
		if (!(*tree))
			get_redir(&(*tree), command);
		else if ((*tree)->left)
			get_tree(&(*tree)->right, command, sig);
		else
			get_tree(&(*tree)->left, command, sig);
	}
	else
	{
		if ((*tree)->left)
			get_tree(&(*tree)->right, command, sig);
		else 
			get_tree(&(*tree)->left, command, sig);
	}
}

void build_tree(t_tree **tree, char **strs)
{
	int		i;
	int		j;
	int		index;
	char	**command;

	i = -1;

	while (strs[++i])
	{
		index = search_pipe(strs, i);
		if (index)
		{
			command = pipe_command(&strs[i], 0, "|");
			get_tree(tree, command, 0);
		}
		if (search_redicrection(&strs[i]))
			get_tree(tree, &strs[i], 1);
		else
		{
			command = pipe_command(&strs[i], 1, NULL);
			get_tree(tree, command, 2);
		}
		i = index;
	}
}

t_tree	*tree_new(char *op)
{
	t_tree	*new;

	new = (t_tree *)malloc(sizeof(t_tree));
	if (!new)
		return (NULL);
	new->left = NULL;
	new->right = NULL;
	if (!op)
		return (new);
	new->strs = ft_calloc(2, sizeof(char *));
	new->strs[0] = ft_strdup(op);
	return (new);
}

void	lvl2(t_tree *node, char **strs, int idx)
{
	int	i;

	i = idx;
	while (strs[i])
	{
		if (strs[i][0] == '>' || strs[i][0] == '<')
		{
			node = tree_new(strs[i]);
			node->right = tree_new(NULL);
			node->right->strs = ft_calloc(2, sizeof(char *));
			node->right->strs[0] = ft_strdup(strs[i+1]);
			lvl2(node->left, strs, i+2);
		}
	}
}

void	lvl1(t_tree *root, char **strs, int idx)
{
	int	i;

	i = idx;
	while(strs[i])
	{
		if (!ft_strcmp(strs[i], "|"))
		{
			root = tree_new(strs[i]);
			free(strs[i]);
			strs[i] = NULL;
			lvl2(root->left, strs, idx);
			lvl1(root->right, strs, i+1);
			return;
		}
		i++;
	}
	lvl2(root, strs, idx);
	return ;
}