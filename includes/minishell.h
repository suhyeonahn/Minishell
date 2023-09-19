/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <suahn@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/03 20:00:59 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 11:53:06 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <signal.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <limits.h>
# include <sys/stat.h>

typedef struct s_input
{
	char		*filename;
	int			fd;
}				t_input;

typedef struct s_output
{
	char		*filename;
	int			fd;
	int			append;
}				t_output;

typedef struct s_cmd
{
	char		*content;
	char		*cmd;
	char		*hd_name;
	char		**argv;
	t_input		input;
	t_output	output;
}				t_cmd;

typedef struct s_cmd_node
{
	t_cmd				*cmd;
	struct s_cmd_node	*next;

}				t_cmd_node;

typedef struct s_cmd_list
{
	t_cmd_node			*start;
}				t_cmd_list;

typedef struct s_sig
{
	int				sigint_hd;
	int				sigint;
	int				sigquit;
	int				exit_status;
	int				syntax_error;
	int				has_child;
	pid_t			pid;
}				t_sig;

// Used only by `parse_commands` to decrease number of lines
typedef struct s_parse_cmd
{
	int				i;
	int				last;
	char			quote;
	t_cmd_list		*cmds;
}				t_parse_cmd;

typedef struct s_tokenize_state
{
	int			i;
	int			last;
	int			in_token;
	t_cmd		*cmd;
}				t_tokenize_state;

// Should contain all fd we are using, like input/outputs currently setup
typedef struct s_mini
{
	int				ret;
	int				cmd_i;
	int				stdout_cpy;
	int				stdin_cpy;
	int				pipe_fd[2];
	pid_t			pid;
	int				parent;
	char			*line;
	t_cmd_list		*cmds;
	t_parse_cmd		*p;
	t_cmd_node		*node;
	char			*substr;
}				t_mini;

typedef struct s_node
{
	char			*s;
	int				is_quote;
	struct s_node	*next;
}				t_node;

typedef struct s_list
{
	t_node	*start;
}				t_list;

typedef struct s_props
{
	int		size;
	int		is_end;
}				t_props;

typedef struct s_quote
{
	int		i;
	int		len;
	int		n_quote;
	char	**quotes_pos;
	char	quote;
}				t_quote;

typedef struct s_var
{
	int		i;
	int		j;
	int		ret;
}				t_var;

typedef struct s_dollar
{
	char	*new;
	int		i;
	int		start;
}				t_dollar;

typedef struct s_identifier
{
	int		start;
	int		done_leading_spaces;
	char	*substr;
}				t_identifier;

typedef struct s_input_delimiter
{
	char	*in;
	char	*buf;
	char	*name;
	int		status;
	char	*tmp;
	char	*delimiter;
}				t_input_delimiter;

typedef struct s_find_path
{
	char		**paths;
	char		*path;
	int			i;
	char		*part_path;
}				t_find_path;

// main.c
void			exit_with_message(t_mini *mini, char **env,
					int ret, char *message);
void			sig_init(void);
void			prompt_line(t_mini *mini, char **env);
void			setting(char **env, char ***new_env);
int				main(int argc, char **argv, char **env);

// mini.c
t_mini			*new_t_mini(void);
void			free_t_mini(t_mini *mini);

// parsing.c
t_cmd			*parse_command(t_mini *mini, char *str, char **env, int cmd_i);
t_cmd			*rdrct_syntax_error(t_tokenize_state *state);
void			handle_quotes(char *str, t_tokenize_state *state);
void			update_in_token(t_tokenize_state *state);
int				char_is_in(char c, char const *set);

// exec.c
int				execute(t_mini *mini, t_cmd *cmd, char ***env);
void			redir_and_exec(t_mini *mini, t_cmd_node *cmd,
					int fd_zero, char ***env);
void			exec_commands(t_mini *mini, char ***env);

// redirect.c
void			set_redirs(int pipe_read, int pipe_write, t_cmd *cmd);
void			parent_redir(t_mini *mini, t_cmd_node *cmd,
					int fd_zero, char ***env);
void			child_redir(t_mini *mini, t_cmd_node *cmd,
					int fd_zero, char ***env);

// exec_utils.c
char			*find_path(char *cmd, char **env);
int				find_slash(char *cmd);
int				has_pipe(t_cmd_node *cmds);
void			free_strarr(char **arr);
char			*ft_strnstr(char *haystack, char *needle, size_t len);
int				ft_memcmp(void *s1, void *s2, size_t n);

// exec.box
void			exec_box(t_mini *mini, t_cmd *cmd, char *path, char ***env);

// cmd_list.c
t_cmd_list		*new_t_cmd_list(void);
void			add_cmd_node_to_list(t_cmd_list *list, t_cmd_node *cmd_node);
void			print_cmd_list(t_cmd_list *list);
t_cmd			*new_t_cmd(void);
t_cmd_node		*new_t_cmd_node(void);

//free_cmd.c
void			free_argv(t_cmd *cmd);
void			free_t_cmd(t_cmd *cmd);
void			free_t_cmd_node(t_cmd_node *cmd_node);
void			free_t_cmd_list(t_cmd_list *list);

// parse_cmd.c
void			syntax_quit(t_parse_cmd *p);
t_parse_cmd		*new_t_parse_cmd(void);
int				parse_commands(t_mini *mini, char **env);
t_cmd_node		*extract_cmd_node(t_mini *mini, int start, int end, char **env);

// builtin.c && ft_cd.c && ft_export.c && ft_exit.c
int				ft_echo(char **argv);
int				ft_cd(char **argv, char ***env);
int				ft_pwd(void);
int				ft_export(char **argv, char ***env);
int				ft_env(char ***env);
int				ft_unset(char **argv, char ***env);
int				ft_exit(t_mini *mini, char **env, char **argv);

// builtin_error.c
int				builtin_error_msg(char *type, char *argv);

// check_builtins.c
void			write_last_letter(char *str, char c, char **tmp);
char			*write_line(char *str, char c);
int				check_builtins(t_mini *mini, t_cmd *cmd, char ***env);

// ctrl.c
void			check_signal_hd(void);
void			check_signal(void);

// init.c
void			new_node(t_node *list, char *str, int quote);
void			init_l(t_list *list, char *str, int quote);
t_list			*create_list(void);
char			**init_new_env_table(char **env);
int				init_quote(char *str, int start);

// ft_split.c
char			**ft_split(char const *s, char c);

// ft_strcmp.c
int				ft_strcmp(char *str1, char *str2);
int				ft_strncmp(char *str1, char *str2, int n);

// ft_strcpy.c
char			*ft_strcpy(char *str);
size_t			ft_strlcpy(char *dst, const char *src, size_t dstsize);

// ft_len.c
size_t			ft_strlen(const char *str);
int				int_len(long n);

// ft_atoi.c
int				ft_atoi(const char *str);
long long		ft_atoi_for_exit(const char *str);

// ft_itoa.c
char			*ft_itoa(int n);

// utils.c
char			*ft_substr(char *s, unsigned int start, size_t len);
char			end_c(int quote);
char			*ft_strjoin(char *s1, char *s2);
int				is_digit(const char *str);
int				check_sign(const char *str, int *i, int *sign);
char			*ft_strjoin2(char *s1, char *s2);

// free.c
int				free_p(t_parse_cmd *p);
void			free_node(t_node *node);
void			free_list(t_list *list);
void			free_env(char **env);

// var_utils.c && has_var.c
int				has_equal(char *str);
int				has_var(char *str);
char			*get_var_value(char **env, char *name);
char			**add_var(char **env, char *var);
char			**delete_var(char **env, char *var);
void			free_var(char **var);

// check_var.c
int				check_var_name(char *str);
int				check_dollar_var_name(char *token);

// env.c
void			modify_shlvl(char ***env);
void			modify_oldpwd(char ***env, char *str);
void			modify_pwd(char ***env, char *str);

// dollar.c
char			*handle_dollar(char *str, char **env);

// dollar_utils.c
char			*var_without_white_space(char *src);
void			write_new_line(char *str, t_dollar *d);
char			*copy_var(char *src, char *new);

// error.c
void			exit_error(char *error);
int				msg_error(t_parse_cmd *p);
void			parse_syntax_error(t_mini *mini);

// parse_utils.c
void			init_t_tokenize_state(t_tokenize_state *state, int cmd_i);
int				in_tab(int i, t_quote *q);
char			*hd_name(int cmd_i);
int				char_is_in(char c, char const *set);

// handle_input_delimiter.c
void			handle_input_delimiter(t_mini *mini, char **env,
					t_tokenize_state *state, char *delimiter);

// parse_command.c
t_cmd			*parse_command(t_mini *mini, char *str, char **env, int cmd_i);

// parse_identifier.c
char			*parse_identifier(char *str, t_tokenize_state *state);

// handle_redirect.c
void			handle_redirect(t_mini *mini, char **env,
					char *str, t_tokenize_state *state);

// close_token.c
void			close_token(char *str, t_tokenize_state *state, char **env);

// handle_output_file.c
void			handle_output_file(t_tokenize_state *state,
					char *identifier, int append);

// handle_input_file.c
void			handle_input_file(t_tokenize_state *state, char *identifier);

// handle_quote.c
void			handle_quotes(char *str, t_tokenize_state *state);
void			update_quote(t_quote *q);
t_quote			*new_t_quote(void);
void			free_t_quote(t_quote *q);

// remove_quote.c
char			*remove_quotes(char *s);
char			*rm_quotes(t_quote *q, char *str);

// handle_plus.c
void			handle_plus(char **argv, char ***env, t_var *v);

extern t_sig	g_sig;

#endif
