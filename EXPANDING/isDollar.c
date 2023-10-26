/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   isDollar.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 16:23:15 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/26 16:24:40 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	check_dollar(char *str)
{
	int	i;

	i = -1;
	while (str[++i])
	{
		if (str[i] == '$' && str[i + 1] != '$' && str[i + 1])
			return (1);
	}
	return (0);
}

void	dollar_valid(t_tree *tree, t_v *v, t_data *env)
{
	tree->flag = 0;
	if (check_dollar(tree->strs[v->i]))
	{
		tree->strs[v->i] = clean_str(tree->strs[v->i], env, tree);
		if (tree->strs[v->i])
		{
			if (tree->flag)
			{
				v->y = -1;
				v->tmp = ft_split(tree->strs[v->i], ' ');
				while (v->tmp[++v->y])
					v->strs[v->j++] = ft_strdup(v->tmp[v->y]);
			}
			else
				v->strs[v->j++] = ft_strdup(tree->strs[v->i]);
		}
	}
	else
	{
		tree->strs[v->i] = remove_quotes(tree->strs[v->i]);
		v->strs[v->j++] = ft_strdup(tree->strs[v->i]);
	}
}
