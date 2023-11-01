/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:33:08 by araji-af          #+#    #+#             */
/*   Updated: 2023/11/01 23:44:13 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialise_exp(t_export *exp)
{
	exp->i = 0;
	exp->status = 0;
	exp->str = NULL;
}

void	free_env(t_data **env)
{
	t_data	*tmp;

	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->variable)
			free(tmp->variable);
		if (tmp->value)
			free(tmp->value);
		free(tmp);
	}
}
