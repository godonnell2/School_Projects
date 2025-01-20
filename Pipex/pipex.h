/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:22:36 by gro-donn          #+#    #+#             */
/*   Updated: 2025/01/20 21:14:40 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ 0  // index for the read end of the pipe
# define WRITE 1 // index for the write end of the pipe
# define IN 0
# define OUT 1
# define SPLIT_BUFF_SIZE 102400

# include <fcntl.h>    // open
# include <limits.h>   //PATH_MAX
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, execve, wait, waitpid, NULL
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
	char	buff[SPLIT_BUFF_SIZE];
	char	buff_two[SPLIT_BUFF_SIZE];
	char	**cmd1_args;
	char	**cmd2_args;
	char	cmd1_fullpath[PATH_MAX];
	char	cmd2_fullpath[PATH_MAX];
}			t_data;

typedef struct s_split_state
{
	size_t	buff_offset;
	size_t	word_count;
	char	**arr;
	size_t	word;
	size_t	word_len;
}			t_split_state;

void		ft_putstring_fd(char *s, int fd);
int			ft_wordlen(char *s);
void		ft_strcpy(char *src, char *dst);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*cat_strs_char(char *dest, const char *src1, char c,
				const char *src2);
void		*ft_memcpy(void *dest, const void *src, size_t n);
char		**ft_split_buff(char const *s, char sep, void *buff);
void		print_usage(void);
t_data		init_data(void);
void		close_data(t_data *data);

void		err_case(t_data *data, char **av);
void		err_case_cmd(t_data *data, char **av, int i);
void		err_case_perror(t_data *data, char **av, int i);

pid_t		first_child(t_data *data, char **av, char **envp);
pid_t		second_child(t_data *data, int ac, char **av, char **envp);
void		resolve_command_full_path(char **envp, char *cmd, char *full_path);
void		ft_printf(const char *mandatory_string, ...);

int			main(int ac, char **av, char **envp);

void		ft_printchar(char c, int fd);
char		*ft_strchr(const char *s, int c);
void		ft_putstr_fd(char *s, int fd);

#endif