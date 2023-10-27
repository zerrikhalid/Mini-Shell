/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_double_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:11 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/27 14:26:39 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*random_file(char *s, int i, char *herdoc)
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
		if (!ft_strncmp(entry_point->d_name, herdoc, 6))
		{
			str = ft_strjoin(str, ft_itoa(i));
			return (closedir(dir), str);
		}
	}
	return (closedir(dir), str);
}

void	signale_handler(int num)
{
	int fds[2];
	
	pipe(fds);
	rl_replace_line("", 0);
	dup2(fds[0], STDIN_FILENO);
	write(fds[1], "\n", 1);
	close(fds[0]); 
	close(fds[1]);
	g_status = -1;
}

int	check_signal(t_vars var)
{
	dup2(var.backup_fd, STDIN_FILENO);
	if (g_status == -1)
	{
		unlink(var.s);
		return (1);	
	}
	return (0);
}

void	ft_l_double_red(t_tree *tree, t_data *envi)
{
	t_vars		var;
	static	int	i;

	var.s = random_file("/tmp/HERDOC", ++i, "HERDOC");
	var.fd = open(var.s, O_CREAT | O_RDWR | O_TRUNC, 0644);
	var.del = clean_str(tree->right->strs[0], envi, tree->right);
	while (1)
	{
		signal(SIGINT, signale_handler);
		if (check_signal(var))
			return ;
		var.str = readline("> ");
		if (!var.str || ft_strcmp(var.str, var.del))	
			break ;
		var.str = clean_str(var.str, envi, tree);
		ft_putstr_fd(var.str, var.fd);
		ft_putstr_fd("\n", var.fd);
		free(var.str);
	}
	free(tree->right->strs[0]);
	tree->right->strs[0] = var.s;
}
