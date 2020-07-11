/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nm_func.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tsedigi <tsedigi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/25 09:14:30 by tsedigi           #+#    #+#             */
/*   Updated: 2018/05/25 09:14:31 by tsedigi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_NM_FUNC_H
# define FT_NM_FUNC_H

# include "ft_nm_struc.h"

int				nm_display_err(char *content, char *err_type);
t_nm_env		*get_nm_env(t_nm_env *env);
void			nm_destroy_env(t_nm_env *env, char opt);
int				ft_nm(const char *const_path, char *path);
int				archi_(char *data);
void			sort_push_table(t_nm_env *env, t_table *table);
int				nm_handle_64(void *data, unsigned int i);
int				nm_handle_32(void *data, unsigned int i);
int				add_table_64(struct nlist_64 table, char *stringtable);
int				add_table_32(struct nlist table, char *stringtable);
int				add_section_64(t_nm_env *env, struct section_64 *sec);
int				add_section_32(t_nm_env *env, struct section *sec);
void			nm_display_64(t_table *tmp);
void			nm_display_32(t_table *tmp, t_nm_env *env);
int				handle_fat_32(void *data, unsigned int i, unsigned int f,
	unsigned int narch);
int				handle_fat_64(void *data, unsigned int i, unsigned int f);
int				nm_handle_64_big(void *data, unsigned int i, int ret);
int				nm_handle_32_big(void *data, unsigned int i, int ret);
int				add_section_64_big(t_nm_env *env, struct section_64 *sec);
int				add_section_32_big(t_nm_env *env, struct section *sec);
int				add_table_64_big(struct nlist_64 table, char *stringtable);
int				add_table_32_big(struct nlist table, char *stringtable);
int				nm_handle_archive(void *data);
void			nm_display_all(t_nm_env *env);
int				check_valid_file(void *data, size_t off);
void			cpu_powerpc_32(unsigned int narch, void *data,
	struct fat_arch *arch);
int				cpu_x86_64_32(unsigned int f, void *data,
	struct fat_arch *arch);
void			cpu_x86_32(unsigned int narch, struct fat_header *h,
	void *data, struct fat_arch *arch);
void			cpu_powerpc_64(unsigned int narch, void *data,
	struct fat_arch_64 *arch);
int				cpu_x86_64_64(unsigned int f, void *data,
	struct fat_arch_64 *arch);
void			cpu_x86_64(unsigned int narch, struct fat_header *h,
	void *data, struct fat_arch_64 *arch);
void			sort_num_table(t_nm_env *env, t_table *table);

#endif
