/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_double_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:11 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/23 22:40:09 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*random_file(char *s, int i)
{
	DIR				*dir;
	struct dirent	*entry_point;

	char *str = ft_strdup(s);
	dir = opendir("/tmp");
	if (!dir)
	{
		ft_printf("Directory you trying to open doesn\'t exist !\n");
		return NULL;
	}
	while ((entry_point = readdir(dir)))
	{
		if (!ft_strncmp(entry_point->d_name, s, 6))
		{
			str = ft_strjoin(str, ft_itoa(i));
			return (str);
		}
	}
	return (str);
}

void	ft_l_double_red(t_tree *tree, t_data *envi, char **env)
{
	char	*str;
	char	*del;
	int		fd;
	int		backup_fd;
	char	*s;
	static	int	i;

	s = random_file("/tmp/HERDOC", ++i);
	backup_fd = dup(STDIN_FILENO);
	fd = open(s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	
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
		fd = open(s, O_RDONLY, 0644);
		dup2(fd, STDIN_FILENO);
		close(fd);
	}
	execute(tree->left, envi, env);
	unlink(s);
	dup2(backup_fd, STDIN_FILENO);
}
 