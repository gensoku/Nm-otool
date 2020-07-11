/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 03:26:07 by tsedigi           #+#    #+#             */
/*   Updated: 2018/09/05 03:26:08 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_otool.h"

static int			print_options(void)
{
	ft_putendl("Usage : ft_tool [-adfht] <object file>...");
	ft_putendl("-a Display the archive header, if the file is an archive");
	ft_putendl("-d Display the contents of the (__DATA,__data) section");
	ft_putendl("-f Display the universal headers.");
	ft_putendl("-h Display the Mach header");
	ft_putendl("-t Display the contents of the (__TEXT,__text) section");
	return (EXIT_FAILURE);
}

static void			init_ot_env(t_ot_env *env)
{
	ft_bzero((void *)&env->hd, sizeof(struct mach_header));
	env->magic = 0;
	env->opts = 0;
	env->curr_archi = 0;
	env->sections = NULL;
	env->file_type = NULL;
	env->archi_name = NULL;
	env->print_path = 0;
	env->fat_enabled = 0;
	env->addr = NULL;
	env->size = 0;
	env->archi = 0;
	get_ot_env(env);
}

static int			check_args_otool(int ac, char const **av, int ret, int i)
{
	if (ac < 2 || !av[i] || ret < 0)
		return (print_options());
	else
	{
		if (!get_ot_env(NULL)->opts)
			check_opts("-t", OPT_LIST, &(get_ot_env(NULL)->opts), LAST_OPTS);
		while (av[i])
		{
			get_ot_env(NULL)->exe_name = ft_strdup(av[i]);
			ret = ft_otool(av[i], NULL);
			ot_destroy_env(get_ot_env(NULL), OT_DESTROY);
			i++;
			if (ret == ARGS_EXIT)
				break ;
		}
	}
	return (ret == EXIT_SUCCESS ? EXIT_SUCCESS : EXIT_FAILURE);
}

int					main(int ac, char const **av)
{
	size_t			i;
	t_ot_env		ot_env;
	int				ret;

	i = 1;
	init_ot_env(&ot_env);
	ret = 0;
	while (av[i] && (ret = check_opts(av[i],
		OPT_LIST, &(get_ot_env(NULL)->opts), LAST_OPTS)) > 0)
		i++;
	return (check_args_otool(ac, av, 0, i));
}
