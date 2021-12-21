/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hdrabi <hdrabi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/20 18:37:18 by hdrabi            #+#    #+#             */
/*   Updated: 2021/12/21 11:40:48 by hdrabi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP
# define PUSH_SWAP

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

typedef struct s_stack
{
	struct s_stack	*prev;
	int				value;
	int				index;
	int				keep;
	struct s_stack	*next;
}	t_stack;

typedef struct s_utils
{
	int	max_size;
	int	lst_size;
	int	max_loop;
	int	group_cp;
	int	group_size;
	int	rot_a;
	int	rot_b;
}	t_utils;

//mini-utils
int		ft_isdigit(char c);
int		ft_strcmp(char *s1, char *s2);
int		ft_max_val(int a, int b);
int		ft_min_val(int a, int b);
int		ft_abs(int n);
int		ft_atoi(char *str);
char	*ft_strjoin(int size, char **strs, char *sep);
char	**ft_split(char const *s, char c);
void	ft_affiche(t_stack *lst);

//lists utils
t_stack	*ft_new_node(int value);
int		ft_lstcount(t_stack *lst);
t_stack	*ft_lstlast(t_stack *lst);
void	ft_lstadd_front(t_stack **lst, t_stack *new);
void	ft_lstadd_back(t_stack **lst, t_stack *new);

//actions
void	ft_swap_a(t_stack **a);
void	ft_swap_b(t_stack **b);
void	ft_push_a(t_stack **b, t_stack **a);
void	ft_push_b(t_stack **a, t_stack **b);
void	ft_rotate_a(t_stack **a, int print);
void	ft_rotate_b(t_stack **b, int print);
void	ft_reverse_rotate_a(t_stack **a, int print);
void	ft_reverse_rotate_b(t_stack **b, int print);
void	ft_rr(t_stack **a, t_stack **b);
void	ft_rrr(t_stack **a, t_stack **b);
void	ft_double_rotate(t_stack **a, t_stack **b, int *rot_a, int *rot_b);
void	ft_rotator(t_stack **a, t_stack **b, int rot_a, int rot_b);

//prepare stack a
int	ft_get_max_loop(t_stack *a, int active);
void	ft_prepare_a(t_stack **a, t_stack **b, t_utils *u, int cur_gp);

//last step
void	ft_last_step(t_stack **a, t_stack **b, t_utils *u);

//others
int	ft_dist_to_top(t_stack *a, int index);

//main functions
t_stack	*ft_devide_args(char **args);
int		ft_check_sort(t_stack *lst);
void 	ft_index_stack(t_stack *a);
void	ft_sort(t_stack **a, t_stack **b);

#endif
