/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/24 20:06:31 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/26 11:21:42 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	fill_final(char **final, char **tmp, int *index, char *operators)
{
	char	c;
	char	*oprators;

	c = 0;
	if (ft_strchr("'\'\"", *(*tmp)))
	{
		c = *(*tmp);
		(*final)[(*index)++] = *(*tmp)++;
		while (*tmp && *(*tmp) != c)
			(*final)[(*index)++] = *(*tmp)++;
		(*final)[(*index)++] = *(*tmp)++;
	}
	else if (ft_strchr(operators, *(*tmp)))
	{
		if (*(*tmp) == '>' || *(*tmp) == '<')
			process_operator(final, tmp, index);
		else
		{
			(*final)[(*index)++] = ' ';
			(*final)[(*index)++] = *(*tmp)++;
			(*final)[(*index)++] = ' ';
		}
	}
	else
		(*final)[(*index)++] = *(*tmp)++;
}

void	helper3(char *str, int *in_quote, int *i, char *c)
{
	*in_quote = 1;
	*c = str[*i];
	(*i)++;
}

void	helper4(int *in_quote, int *i, char *c)
{
	*in_quote = 0;
	*c = 0;
	(*i)++;
}
