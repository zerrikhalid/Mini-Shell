/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_double_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:11 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/23 11:12:42 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_l_double_red(t_tree *tree, t_data *envi, char **env)
{
	char	*str;
	char	*del;
	int		fd;
	int	backup_fd;

	backup_fd = dup(STDIN_FILENO);
	fd = open("HERDOC", O_CREAT | O_RDWR | O_TRUNC, 0644);
	del = ft_strdup(tree->right->strs[0]);
	while (1)
	{
		str = readline("heredoc > ");
		if (!str || ft_strcmp(str, del))
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	if (tree->left && (tree->left->strs[0][0] != '<' || tree->left->strs[0][0] != '<'))
	{
		close(fd);
		fd = open("HERDOC", O_RDONLY, 0644);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	execute(tree->left, envi, env);
	dup2(backup_fd, STDIN_FILENO);
}
 