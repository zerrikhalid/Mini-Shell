/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/25 18:29:26 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/27 14:38:21 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	process_operator(char **final, char **str, int *index)
{
	char	c;

	c = *(*str);
	(*final)[(*index)++] = ' ';
	(*final)[(*index)++] = *(*str);
	if (*(*str) == '<' || *(*str) == '>')
	{
		if (*((*str) + 1) == c)
		{
			(*final)[(*index)++] = *((*str) + 1);
			(*str)++;
		}
	}
	(*final)[(*index)++] = ' ';
	(*str)++;
}

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
