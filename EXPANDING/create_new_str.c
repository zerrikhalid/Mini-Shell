/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_new_str.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 12:45:49 by kzerri            #+#    #+#             */
/*   Updated: 2023/10/28 14:25:08 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	bring_dequoted_value(char *str, int i, char *s, int j)
{
	while (str[i])
	{
		if (str[i] == '\'')
			break ;
		s[j++] = str[i];
		i++;
	}
	return (i);
}

int	create_new_str(char *str, char *s, int i, t_data *env)
{
	t_var	var;

	var.j = ft_strlen(s);
	var.fr = var.tmp;
	if (i >= 1 && str[i - 1] == '\'')
		i = bring_dequoted_value(str, i, s, var.j);
	else
	{
		while (str[i])
		{
			if (str[i] == '\"')
				break ;
			if (str[i] == '$')
			{
				var.tmp = get_var_value(str, &i, env);
				while (*var.tmp)
					s[var.j++] = *var.tmp++;
				continue ;
			}
			s[var.j++] = str[i];
			i++;
		}
	}
	return (free_var(var.fr), i);
}
