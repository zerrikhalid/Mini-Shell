/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   left_double_r.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/07 18:37:11 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/21 13:43:24 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	ft_l_double_red(t_tree *tree, t_data *envi, char **env)
{
	char	*str;
	char	*del;
	int		fd;

	fd = open("HERDOC", O_CREAT | O_RDWR | O_APPEND, 0644);
	del = ft_strdup(tree->right->strs[0]);
	while (1)
	{
		str = readline("heredoc > ");
		if (str)
		{
			if (ft_strcmp(str, del))
				break ;
		}
		else
			break ;
		ft_putstr_fd(str, fd);
		ft_putstr_fd("\n", fd);
	}
	unlink("HERDOC");
}
