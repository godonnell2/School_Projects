/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/26 00:51:43 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/11 10:27:58 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
#define PUSH_SWAP_H

#define INT_MAX 2147483647
#define INT_MIN -2147483648
#define MAX_ARGS 1000

#include <limits.h>
#include <stddef.h> //size_t
#include <stdlib.h> // malloc, free, exit, get ENV var
#include <unistd.h> // write, read, close
#include <stdio.h>

typedef struct s_stack
{
	int nbr;
	int index;
	int best;
	int cost;
	struct s_stack *next;
} t_stack;

/* Utils */
char **ft_split(char *str, char delimiter);
void check_int_max(int ac, char **av);
long int ft_atol(const char *str);
void parse_sign_and_whitespace(const char **str, int *sign);
void free_arr(int ac, char **av);

/* Check Arguments */
int is_in_range(const char *str);
int has_duplicates(int *arr, int size);
int is_numeric(const char *str);
void check_args(int ac, char **av);
int is_valid_split(char **split_args);
void err_case(int ac, char **av);
void err_case_nofree(void);
int count_split_args(char **split_args);

/* stack utils */
t_stack *add_args_to_stack(char **av);
int struct_len(t_stack *stack);
int struct_sum(t_stack *stack);
void free_stack(t_stack **head);
void insert_end(t_stack **root, int value);
void free_stack(t_stack **root);
void rotate_to_top_a(t_stack **a, int index);
void rotate_to_top_b(t_stack **b, int index);
int find_lowest_cost(t_stack *b);
int check_sorting(t_stack **a);
int struct_len(t_stack *root);
int struct_sum(t_stack *root);
t_stack *add_data(int ac, char **av);

/* Actions */
void move_top_element(t_stack **src_stack, t_stack **dst_stack);
void push_to_stack_b(t_stack **stack_a, t_stack **stack_b);
void push_to_stack_a(t_stack **stack_b, t_stack **stack_a);
void rotate_stack(t_stack **stack_head);
void ra(t_stack **a);
void rb(t_stack **b);
void rrotate_stack(t_stack **stack_head);
void reverse_rotate_stack_a(t_stack **stack_a);
void reverse_rotate_stack_b(t_stack **stack_b);
void swap_top_two(t_stack **stack_head);
void swap_stack_a(t_stack **stack_a);
void swap_stack_b(t_stack **stack_b);

/* Sorting*/
int check_sorting(t_stack **a);
void insert_end(t_stack **head, int value);
void sorting(t_stack **a, t_stack **b);
void sort_2(t_stack **a);
void sort_3(t_stack **a);
void sort_4(t_stack **a, t_stack **b);
void sort_5(t_stack **a, t_stack **b);
void pos_4(t_stack **a, t_stack **b);
void pos_3(t_stack **a, t_stack **b);
int find_best_friend(t_stack *a, int nbr_b);
void set_best_friend(t_stack *a, t_stack **b);
void set_index(t_stack **node);
int get_moves_to_top(t_stack *node, int index);
void set_cost(t_stack **a, t_stack **b);
void moves_top(t_stack **a, t_stack **b);
int find_lowest_cost(t_stack *b);
void rotate_to_top_a(t_stack **a, int index);
void rotate_to_top_b(t_stack **b, int index);
void findmean_below_pushb(t_stack **a, t_stack **b);
void sort_greater_than_five(t_stack **a, t_stack **b);
void rotate_to_finalpos(t_stack **a);
void print_stack(t_stack *s, char *comment);

#endif /* PUSH_SWAP_H */
