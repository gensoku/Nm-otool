/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 09:05:27 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/25 09:05:29 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

static void			init_nm_env(t_nm_env *env)
{
	env->opts = 0;
	env->curr_archi = 0;
	env->sections = NULL;
	env->archi_name = NULL;
	env->tables = NULL;
	env->print_path = 0;
	env->fat_enabled = 0;
	env->addr = NULL;
	env->size = 0;
	get_nm_env(env);
}

static int			loop_args(char const **av, int ret, int i)
{
	if (!av)
		return (ret);
	while (av[i])
	{
		get_nm_env(NULL)->exe_name = ft_strdup(av[i]);
		ret = ft_nm(av[i], NULL);
		nm_destroy_env(get_nm_env(NULL), NM_DESTROY);
		i++;
	}
	return (ret);
}

int					main(int ac, char const **av)
{
	size_t			i;
	t_nm_env		nm_env;
	int				ret;

	i = 1;
	init_nm_env(&nm_env);
	ret = 0;
	while (av[i] && check_opts(av[i], OPT_LIST,
		&(get_nm_env(NULL)->opts), SET_OPTS))
		i++;
	if (ac < 2 || !av[i])
	{
		if (ft_nm("a.out", NULL))
			return (EXIT_FAILURE);
	}
	else
	{
		if (av[i] && av[i + 1])
			get_nm_env(NULL)->print_path = 1;
		ret = loop_args(&av[i], EXIT_SUCCESS, 0);
	}
	return (ret ? EXIT_SUCCESS : EXIT_FAILURE);
}
