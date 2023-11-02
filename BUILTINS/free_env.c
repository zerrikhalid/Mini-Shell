/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/31 17:33:08 by araji-af          #+#    #+#             */
/*   Updated: 2023/11/02 20:06:43 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	initialise_exp(t_export *exp)
{
	exp->i = 0;
	exp->status = 0;
	exp->str = NULL;
	exp->tmp = NULL;
}

void	free_env(t_data **env)
{
	t_data	*tmp;

	if (!env)
		return ;
	while (*env)
	{
		tmp = *env;
		*env = (*env)->next;
		if (tmp->variable)
			free(tmp->variable);
		if (tmp->value)
			free(tmp->value);
		if (tmp)
			free(tmp);
	}
}
