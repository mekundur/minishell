/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pvasilan <pvasilan@student.42berlin.de>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/12 17:07:01 by rmei              #+#    #+#             */
/*   Updated: 2025/01/24 15:45:59 by pvasilan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

# include <stdlib.h>
# include <signal.h>

# define MAXARGS 30

typedef struct s_garbage
{
	void				*ptr;
	struct s_garbage	*next;
}	t_garbage;

typedef struct s_mini
{
	int			exit_status;
	char		**env;
	char		**env_backup;
	t_garbage	*gc_list;
}	t_mini;

typedef struct s_cmd
{
	int	type;
}	t_cmd;

typedef struct s_execcmd
{
	int		type;
	char	*argv[MAXARGS];
	char	*eargv[MAXARGS];
}	t_execcmd;

//file -> start of command
// efile -> end of command and args
typedef struct s_redircmd
{
	int		type;
	int		fd;
	int		mode;
	char	*file;
	char	*efile;
	char	*delim;
	t_cmd	*cmd;
}	t_rdcmd;

typedef struct s_pipecmd
{
	int		type;
	t_cmd	*left;
	t_cmd	*right;
}	t_pipecmd;

typedef struct s_backcmd
{
	int		type;
	t_cmd	*cmd;
}	t_backcmd;

typedef struct s_heredoccmd
{
	int		type;
	char	*delim;
	char	*content;
	t_cmd	*cmd;
}	t_heredoccmd;

typedef struct s_exbuffer
{
	char	*expanded;
	char	*p;
	size_t	buffersize;
}	t_exbuffer;

typedef struct s_tokenizer {
	char	*start;
	char	*end;
	char	*tok_start;
	char	*tok_end;
	bool	in_single; 
	bool	in_double; 
	char	*symbols;
}	t_tokenizer;

typedef struct s_redir_params
{
	t_mini	*mini;
	t_cmd	*subcmd;
	char	*file;
	char	*efile;
	int		mode;
	int		fd;
}	t_redir_params;

typedef struct s_delim_info {
	int		start;
	int		end;
	bool	in_quotes;
	bool	found_start;
	char	quote_char;
	int		i;
	int		j;
	char	*delim;
}	t_delim_info;

#endif
