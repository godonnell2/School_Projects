/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gro-donn <gro-donn@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/29 08:22:36 by gro-donn          #+#    #+#             */
/*   Updated: 2024/12/29 18:28:19 by gro-donn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# define READ_END 0  // index for the read end of the pipe
# define WRITE_END 1 // index for the write end of the pipe

# include <fcntl.h>    // open
# include <stdio.h>    // perror
# include <stdlib.h>   // exit, malloc, free, execve, wait, waitpid, NULL
# include <sys/wait.h> // wait, waitpid
	// This header file provides macros related to process termination.
// It includes declarations for functions like wait and waitpid,
// which are used to wait for state changes in child processes.
# include <unistd.h> //access, close, dup2, execve, fork, pipe, read, write

typedef struct s_data
{
	char	*cmd;
	char	**args_cmds;
	int		pipe_fd[2];
	int		input_fd;
	int		output_fd;
	pid_t	pid1;
	pid_t	pid2;
}			t_data;

void		ft_putstr_fd(char *s, int fd);
int			ft_wordlen(char *s);
int			ft_strncmp(const char *s1, const char *s2, size_t n);
char		*cat_strs_char(char *dest, const char *src1, char c,
				const char *src2);
char		**ft_split(char const *s, char c);
void		print_usage(void);
void		init_data(t_data **tmp);
void		err_case(const char *msg, t_data *data);
pid_t		first_child(t_data *data, char **av, char **envp);
pid_t		second_child(t_data *data, int ac, char **av, char **envp);
int			main(int ac, char **av, char **envp);

#endif