/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nm_section_32.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/10 01:40:44 by tsedigi           #+#    #+#             */
/*   Updated: 2018/08/10 01:40:45 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_nm.h"

int				add_section_32(t_nm_env *env, struct section *sec)
{
	t_section	*section;
	t_section	*tmp;

	if ((section = (t_section *)malloc(sizeof(t_section))) == NULL)
		return (nm_display_err(NULL, NM_MALLOC_FAIL));
	section->name = ft_strdup(sec->sectname);
	section->next = NULL;
	tmp = env->sections;
	if (!tmp)
	{
		env->sections = section;
		section->id = 1;
		return (0);
	}
	while (tmp->next)
		tmp = tmp->next;
	tmp->next = section;
	section->id = tmp->id + 1;
	return (0);
}
