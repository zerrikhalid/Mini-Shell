/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kzerri <kzerri@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/04 21:04:35 by araji-af          #+#    #+#             */
/*   Updated: 2023/10/31 18:44:04 by kzerri           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	no_option_export(t_data *envi)
{
	while (envi)
	{
		printf("declare -x %s", envi->variable);
		if (envi->value)
			printf("=\"%s\"\n", envi->value);
		else
			printf("\n");
		envi = envi->next;
	}
}

void	initialize_exp_variable(t_export *var, char *av, t_data *envi)
{
	var->end = get_var_lenght(av);
	var->end1 = get_value_lenght(var->end, av);
	if (var->str)
		free(var->str);
	var->str = ft_substr(av, 0, var->end);
	var->tmp = get_variable(envi, var->str);
}

void	append_operation(t_export *exp, char *av, t_data **envi)
{
	if (!exp->tmp)
	{
		exp->tmp = ft_mylstnew(ft_substr(av, 0, exp->end),
				ft_substr(av, exp->end + 2, exp->end1));
		if (!envi || !*envi)
			*envi = exp->tmp;
		else
			ft_lstadd_back(envi, exp->tmp);
	}
	else if (exp->tmp)
	{
		exp->str = exp->tmp->value;
		exp->tmp->value = my_strjoin(exp->str,
				ft_substr(av, exp->end + 2, exp->end1));
		if (exp->str)
			free(exp->str);
		exp->str = NULL;
	}
}

void	create_update(t_export *exp, char *av, t_data **envi)
{
	if (!exp->tmp)
	{
		exp->tmp = ft_mylstnew(ft_substr(av, 0, exp->end),
				ft_substr(av, exp->end + 1, exp->end1));
		if (!envi || !*envi)
			*envi = exp->tmp;
		else
			ft_lstadd_back(envi, exp->tmp);
	}
	else
	{
		free(exp->tmp->value);
		exp->tmp->value = ft_substr(av, exp->end + 1, exp->end1);
	}
}

int	export(char **av, t_data **envi)
{
	t_export	exp;

	initialise_exp(&exp);
	if (!*av)
		no_option_export(*envi);
	while (av[exp.i])
	{
		initialize_exp_variable(&exp, av[exp.i], *envi);
		if (!check_export_args(av[exp.i], &exp.status))
			exp.i++;
		else
		{
			if (check_append_new(av[exp.i]) == 0)
				create_new_var(&exp, av[exp.i], envi);
			else if (check_append_new(av[exp.i]) == 1)
				append_operation(&exp, av[exp.i], envi);
			else
				create_update(&exp, av[exp.i], envi);
			exp.i++;
		}
	}
	if (exp.str)
		free(exp.str);
	return (exp.status);
}
