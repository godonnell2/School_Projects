/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:22:36 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/12 20:01:51 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0  // index for the read end of the pipe
# define WRITE_END 1 // index for the write end of the pipe
# define SPLIT_BUFF_SIZE (100 * 1024) 

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <limits.h>  //PATH_MAX
# include <stdlib.h>   // exit, malloc, free, execve, wait, waitpid, NULL
# include <sys/wait.h> // wait, waitpid
						// provides macros related to process termination.
// It includes declarations for functions like wait and waitpid,
// which are used to wait for state changes in child processes.
# include <unistd.h> //access, close, dup2, execve, fork, pipe, read, write

typedef struct s_data
{
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	pid_t	pid1;
	pid_t	pid2;
}			t_data;

typedef struct s_split_state
{
	size_t		buff_offset;
	size_t		word_count;
	char		**arr;
	size_t		word;
	size_t		word_len;
}				t_split_state;

void		ft_putstr_fd(char *s, int fd);
int			ft_wordlen(char *s);
void ft_strcpy(char *src, char *dst);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*cat_strs_char(char *dest, const char *src1, char c,
				const char *src2);
void *ft_memcpy(void *dest, const void *src, size_t n);
//char		**ft_split(char const *s, char c);
char **ft_split_buff(char const *s, char sep, void *buff);
void		print_usage(void);
t_data		init_data();
void		err_case(const char *msg, t_data *data);
pid_t		first_child(t_data *data, char **av, char **envp);
pid_t		second_child(t_data *data, int ac, char **av, char **envp);
void		find_fullpath(char **envp, char *cmd, char* full_path);
int			main(int ac, char **av, char **envp);

#endif