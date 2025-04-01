/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/07 13:36:09 by lsasse            #+#    #+#             */
/*   Updated: 2025/04/01 17:56:01 by mekundur         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H
# define _GNU_SOURCE

// Includes //
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <string.h>
# include <signal.h>
# include <stdbool.h>
# include <errno.h>
# include <dirent.h>
# include "libft.h"
# include "macros.h"
# include "structs.h"

extern int	*g_exit_status;

// Garbage collector functions
void	*gc_add(t_mini *mini, void *ptr);
void	gc_free(t_mini *mini, void *ptr);
void	gc_cleanup(t_mini *mini);

/* MINISHELL */
void	minishell(char *buf, t_mini *mini);
void	ft_builtin_exec(char **argv, t_mini *mini);
int		get_cmd(char *buf, int nbuf, t_mini *mini);
char	*ft_fgets(char *str, int n, t_mini *mini, FILE *stream);
void	panic(char *msg, t_mini *mini);
void	cmd_run(t_cmd *cmd, t_mini *mini);

/* SIGNALS */
void	standard_signal_setup(void);

/* BUILTINS */
void	ft_cd(char **argv, t_mini *mini);
void	ft_echo(char **argv, t_mini *mini);
void	ft_env(char **argv, t_mini *mini);
void	ft_unset(char **argv, t_mini *mini);
void	ft_export(char **argv, t_mini *mini);
void	ft_export_print(char **argv, t_mini *mini);
void	ft_exit(char **argv, t_mini *mini);
void	ft_pwd(t_mini *mini);

/* CONSTRUCTORS */
t_cmd	*exec_cmd(t_mini *mini);
t_cmd	*pipe_cmd(t_mini *mini, t_cmd *left, t_cmd *right);
t_cmd	*back_cmd(t_mini *mini, t_cmd *subcmd);
t_cmd	*heredoc_cmd(t_mini *mini, t_cmd *subcmd, char *delim, char *content);
void	heredoc_handler_coda(pid_t pid, t_mini *mini);

/* EXEC */
void	ft_back(t_cmd *cmd, t_mini *mini);
void	ft_fork_l(t_cmd *left, int *p, t_mini *mini);
void	ft_fork_r(t_cmd *right, int *p, t_mini *mini);
void	ft_pipe(t_cmd *cmd, t_mini *mini);
void	ft_redir(t_cmd *cmd, t_mini *mini);
void	ft_heredoc(t_rdcmd *cmd, t_mini *mini);
void	heredoc_signal_handler(int sig);
void	setup_heredoc_signals(void);

/* PARSING */
int		token_get(char **ps, char *es, char **q, char **eq);
int		peek(char **ps, char *es, char *toks);
t_cmd	*str_null_terminate(t_cmd *cmd);
t_cmd	*cmd_parse(char *s, t_mini *mini);
t_cmd	*ft_line_parse(char **ps, char *es, t_mini *mini);
t_cmd	*ft_pipe_parse(char **ps, char *es, t_mini *mini);
t_cmd	*ft_redirs_parse(t_cmd *cmd, char **ps, char *es, t_mini *mini);
t_cmd	*ft_block_parse(char **ps, char *es, t_mini *mini);
t_cmd	*ft_exec_parse(char **ps, char *es, t_mini *mini, int argc);
t_list	*rev_redir_lst(t_cmd *cmd, t_mini *mini);
void	ft_redir_file(t_rdcmd *rcmd);

/* UTILS */
int		ft_2dstrlen(char **str);
char	*ft_getenv(char *variable, char **env);
char	**ft_2dstrcpy(char **arg, int len, t_mini *mini);
char	**ft_2dstr_realloc(char **str, int newsize, t_mini *mini);
void	ft_2dstrfree(char **str);
void	ft_multi_free(char *s1, char *s2, char *s3, char *s4);
void	ft_execvp(char *file, char **args, t_mini *mini);
int		ft_is_whitespace(char s);
char	*ft_strtok(char *str, const char *delim);
void	ft_exit_status_parent(t_mini *mini);
void	ft_exit_status_child(t_mini *mini);
void	ft_set_pwd_var(t_mini *mini, char cwd[100]);
void	ft_set_oldpwd_var(t_mini *mini, char cwd[100]);
bool	ft_has_flags(char **argv);
int		ft_is_single_quote(char c);
int		ft_is_double_quote(char c);
char	*ft_slice(char *str, int start, int end);
char	*ft_expand_vars(const char *s, t_mini *mini);
char	*buffer_alloc(size_t *buffer_size);
void	*ft_realloc(void *ptr, size_t new_size);
void	check_merged_arg(char **merged_arg, char *part);
char	*handle_quotes(char **argv);
void	ft_remove_trailing_new_line(char *str);
char	*ft_remove_quotes(char *str);
void	toggle_quotes(bool *in_single_quote, bool *in_double_quote, char quote);
char	*ft_get_delim(char *file);

/* ERROR HANDLING */
void	handle_error(const char *message, t_mini *mini);
bool	buffer_ensure_capacity(t_exbuffer *buffer, size_t needed_space);
void	char_copy(t_exbuffer *buffer, char c);

// Variable expansion helper functions
void	copy_value_to_buffer(t_exbuffer *buff, const char *value);

// Quote handling and main processing
void	handle_quote(const char **s, bool *in_quote, t_exbuffer *buff);
char	*ft_expand_vars(const char *s, t_mini *mini);
void	process_input_str(const char *s, t_exbuffer *buff, 
			char **this_env, t_mini *mini);
void	expand_curly_variable(const char **s,
			t_exbuffer *buff, char **this_env);
char	*extract_var_name_len(const char *start, size_t *var_len);
void	put_nbr_to_buffer(t_exbuffer *buff, int n);
char	*get_curly_var_name(const char **s);
char	*ft_generate_file_names(char file[100]);
t_cmd	*redircmd_in(t_mini *mini, t_cmd *subcmd, char *file, char *efile);
t_cmd	*redircmd_out(t_mini *mini, t_cmd *subcmd, char *file, char *efile);
t_cmd	*redircmd_append(t_mini *mini, t_cmd *subcmd, char *file, char *efile);
t_rdcmd	*create_base_redircmd(t_cmd *subcmd, char *file, char *efile);

#endif
