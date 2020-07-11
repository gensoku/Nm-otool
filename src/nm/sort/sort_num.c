/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_num.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/04 03:35:53 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/04 03:35:54 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static int			loop_check_num(t_table *elem,
	t_table *tmp, unsigned long opts)
{
	if ((elem->type == 'u' || elem->type == 'U')
		&& (tmp->type != 'u' && tmp->type != 'U') && !is_opt_set(opts, 'r'))
		return (1);
	if ((elem->type == 'u' || elem->type == 'U')
		&& (tmp->type != 'u' && tmp->type != 'U') && is_opt_set(opts, 'r'))
		return (0);
	if ((elem->type != 'u' && elem->type != 'U')
		&& (tmp->type == 'u' || tmp->type == 'U') && is_opt_set(opts, 'r'))
		return (1);
	if ((elem->type != 'u' && elem->type != 'U')
		&& (tmp->type == 'u' || tmp->type == 'U'))
		return (0);
	if ((!is_opt_set(opts, 'r') && ft_strcmp(elem->name, tmp->name) < 0)
		|| (is_opt_set(opts, 'r') && ft_strcmp(elem->name, tmp->name) > 0))
		return (1);
	return (0);
}

static int			check_add_num(t_table *elem, t_table *tmp,
	unsigned long opts)
{
	if ((elem->value < tmp->value && !is_opt_set(opts, 'r'))
		|| (elem->value > tmp->value && is_opt_set(opts, 'r')))
	{
		return (1);
	}
	if (elem->value == tmp->value && elem->value != 0)
	{
		if ((!is_opt_set(opts, 'r') && ft_strcmp(elem->name, tmp->name) < 0)
			|| (is_opt_set(opts, 'r') && ft_strcmp(elem->name, tmp->name) > 0))
		{
			return (1);
		}
		return (0);
	}
	if (elem->value == tmp->value && elem->value == 0)
		return (loop_check_num(elem, tmp, opts));
	return (0);
}

void				sort_num_table(t_nm_env *env, t_table *table)
{
	t_table			*tmp;
	unsigned long	opts;

	tmp = env->tables;
	opts = env->opts;
	if (check_add_num(table, tmp, opts))
	{
		table->next = tmp;
		env->tables = table;
		return ;
	}
	while (tmp->next)
	{
		if (check_add_num(table, tmp->next, opts))
		{
			table->next = tmp->next;
			tmp->next = table;
			return ;
		}
		tmp = tmp->next;
	}
	if (tmp)
		tmp->next = table;
}
