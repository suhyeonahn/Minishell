/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: suahn <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/02 14:09:31 by suahn             #+#    #+#             */
/*   Updated: 2022/05/07 12:44:07 by suahn            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_parse_cmd	*new_t_parse_cmd(void)
{
	t_parse_cmd	*parse;

	parse = malloc(sizeof(t_parse_cmd));
	if (!parse)
		return (NULL);
	parse->i = 0;
	parse->last = 0;
	parse->quote = '\0';
	parse->cmds = new_t_cmd_list();
	return (parse);
}

void	syntax_quit(t_parse_cmd *p)
{
	if (g_sig.syntax_error == 1)
	{
		g_sig.exit_status = 2;
		free_p(p);
	}
}

int	mini_parse_command(t_parse_cmd *p, t_mini *mini, char **env)
{
	while (p->i <= (int)ft_strlen(mini->line) && mini->line[p->i] != '\0')
	{
		if (p->i == p->last && (mini->line[p->i] == ' '
				|| mini->line[p->i] == '|'))
		{
			while (mini->line[p->i] == ' ')
				p->i++;
			if (mini->line[p->i] == '|')
				return (msg_error(p));
		}
		if (p->quote == '\0' && (mini->line[p->i] == '\''
				|| mini->line[p->i] == '\"'))
			p->quote = mini->line[p->i];
		else if (p->quote != '\0' && p->quote == mini->line[p->i])
			p->quote = '\0';
		else if (p->quote == '\0' && mini->line[p->i] == '|')
		{
			add_cmd_node_to_list(p->cmds,
				extract_cmd_node(mini, p->last, p->i, env));
			syntax_quit(p);
			p->last = p->i + 1;
		}
		p->i++;
	}
	return (0);
}

int	parse_commands(t_mini *mini, char **env)
{
	t_parse_cmd	*p;

	p = new_t_parse_cmd();
	mini->p = p;
	mini->cmd_i = 0;
	if (mini_parse_command(p, mini, env) == 2)
		return (2);
	if (p->quote != '\0')
	{
		write(1, "minishell: syntax error: unclosed quote\n", 40);
		parse_syntax_error(mini);
	}
	if (mini->line[ft_strlen(mini->line) - 1] == '|')
	{
		write(2, "minishell: syntax error near unexpected token '|'\n", 50);
		parse_syntax_error(mini);
	}
	if (g_sig.syntax_error == 1)
		return (free_p(p));
	add_cmd_node_to_list(p->cmds, extract_cmd_node(mini, p->last, p->i, env));
	if (g_sig.syntax_error == 1)
		return (free_p(p));
	mini->cmds = p->cmds;
	free(p);
	return (mini->ret);
}

t_cmd_node	*extract_cmd_node(t_mini *mini, int start, int end, char **env)
{
	t_cmd_node	*node;
	char		*substr;

	node = new_t_cmd_node();
	mini->node = node;
	free(node->cmd->argv);
	free(node->cmd);
	substr = ft_substr(mini->line, start, (end - start));
	mini->substr = substr;
	mini->cmd_i++;
	node->cmd = parse_command(mini, substr, env, mini->cmd_i);
	if (g_sig.syntax_error == 1 || node->cmd == NULL)
	{
		free(mini->substr);
		free(mini->node);
		return (NULL);
	}
	node->cmd->content = substr;
	return (node);
}
