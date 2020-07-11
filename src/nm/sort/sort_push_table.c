/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_push_table.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/07 04:24:20 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/07 04:24:21 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int			check_asci(t_table *t1, t_table *t2, unsigned long opts)
{
	if (!ft_strcmp(t1->name, t2->name) && !is_opt_set(opts, 'r')
		&& t1->value < t2->value)
		return (1);
	else if (!ft_strcmp(t1->name, t2->name) && is_opt_set(opts, 'r')
		&& t1->value > t2->value)
		return (1);
	else if (ft_strcmp(t1->name, t2->name) < 0 && !is_opt_set(opts, 'r'))
		return (1);
	else if (ft_strcmp(t1->name, t2->name) > 0 && is_opt_set(opts, 'r'))
		return (1);
	return (0);
}

static void			sort_asc_table(t_nm_env *env, t_table *table,
	t_table *tmp, unsigned long opts)
{
	tmp = env->tables;
	opts = env->opts;
	if ((ft_strcmp(table->name, tmp->name) < 0 && !is_opt_set(opts, 'r'))
		|| (ft_strcmp(table->name, tmp->name) > 0 && is_opt_set(opts, 'r'))
		|| (!ft_strcmp(table->name, tmp->name) && !is_opt_set(opts, 'r')
		&& table->value < tmp->value)
		|| (!ft_strcmp(table->name, tmp->name) && is_opt_set(opts, 'r')
		&& table->value > tmp->value))
	{
		table->next = tmp;
		env->tables = table;
		return ;
	}
	while (tmp->next)
	{
		if (check_asci(table, tmp->next, opts))
		{
			table->next = tmp->next;
			tmp->next = table;
			return ;
		}
		tmp = tmp->next;
	}
	(tmp) ? tmp->next = table : 0;
}

void				sort_push_table(t_nm_env *env, t_table *table)
{
	t_table			*tmp;

	tmp = env->tables;
	if (!tmp)
	{
		env->tables = table;
		return ;
	}
	if (is_opt_set(env->opts, 'p'))
	{
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = table;
	}
	else if (is_opt_set(env->opts, 'n'))
		sort_num_table(env, table);
	else
		sort_asc_table(env, table, NULL, 0);
}
