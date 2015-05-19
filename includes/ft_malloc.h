/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_malloc.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cfriot <cfriot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2015/02/28 07:55:31 by cfriot            #+#    #+#             */
/*   Updated: 2015/03/23 16:57:01 by cfriot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_MALLOC_H
# define FT_MALLOC_H
# include <sys/mman.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/resource.h>
# include <stdlib.h>
# define SML 4096
# define TIN 1024

typedef struct		s_lrg
{
	void			*addr;
	size_t			size;
	struct s_lrg	*next;
}					t_lrg;

typedef struct		s_sml
{
	void			*addr;
	long			small[1600][3];
	int				nb_small;
	int				tot_size_small;
	int				tot_block;
	struct s_sml	*next;
}					t_sml;

typedef struct		s_tin
{
	void			*addr;
	long			tiny[1600][3];
	int				nb_tiny;
	int				tot_size_tiny;
	int				tot_block;
	struct s_tin	*next;
}					t_tin;

typedef struct		s_env
{
	struct s_sml	*sml;
	struct s_tin	*tin;
	struct s_lrg	*lrg;
}					t_env;

extern t_env		g_env;

void				free(void *addr);
int					ft_free_small(void *addr, t_sml *sml);
int					ft_free_tiny(void *addr, t_tin *tin);
int					ft_free_large(void *addr);
void				*ft_run_sml_lst(size_t size);
void				*ft_run_tin_lst(size_t size);
void				*malloc(size_t size);
void				*realloc(void *ptr, size_t size);
void				*ft_malloc_small(size_t size);
void				*ft_realloc_small(void *ptr, size_t size, t_sml *sml);
void				*ft_search_space_small(size_t size, t_sml *sml);
void				*ft_update_env_small(int i, size_t size, t_sml *sml);
void				ft_check_leaks_small(int i, int nb_case, t_sml *sml);
void				*ft_malloc_tiny(size_t size);
void				*ft_realloc_tiny(void *ptr, size_t size, t_tin *tin);
void				*ft_search_space_tiny(size_t size, t_tin *tin);
void				*ft_update_env_tiny(int i, size_t size, t_tin *tin);
void				ft_check_leaks_tiny(int i, int nb_case, t_tin *tin);
void				*ft_malloc_large(size_t size);
void				*ft_realloc_large(void *ptr, size_t size);
void				*ft_magic_shit(void *ptr, size_t size,
					int mod, size_t old_size);
void				*ft_memcpy(void *dst, const void *src, size_t size);
void				*ft_from_tiny_to_small(void *ptr, size_t size, t_tin *tin);
void				*ft_from_small_to_large(void *ptr, size_t size, t_sml *sml);
void				*ft_try_small(void *addr);
void				*ft_try_tiny(void *addr);
void				*ft_try_large(void *addr);
void				show_alloc_mem(void);
void				ft_display_info_tiny(t_tin *cursor);
long				show_tiny(void);
void				ft_display_info_small(t_sml *cursor);
long				show_small(void);
void				ft_destroy_sml(t_sml *sml);
void				ft_destroy_tin(t_tin *tin);
void				ft_ini_env(void);
void				ft_ini_sml(t_sml *sml);
void				ft_ini_tin(t_tin *tin);
void				ft_putstr_malloc(char *str);
int					ft_strlen_malloc(char *str);
void				ft_putchar_malloc(char c);
void				ft_putbase_malloc(long nbr, int base);
void				ft_print_tot(long tot);
void				*ft_make_realloc_tiny(void *ptr, size_t size);
void				*ft_make_realloc_small(void *ptr, size_t size);
void				*ft_make_realloc_large(void *ptr, size_t size);
void				ft_clear_small(t_sml *sml);
void				ft_clear_tiny(t_tin *tin);
#endif
