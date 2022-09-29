/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 14:59:49 by ncathy            #+#    #+#             */
/*   Updated: 2022/08/19 14:59:49 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_parser	*init_parser(void)
{
	t_parser	*parser;

	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->fd_read = -1;
	parser->fd_write = -1;
	parser->count = 0;
	parser->cmd_list = NULL;
	parser->cmd_name = NULL;
	return (parser);
}

int	check_all_tokens(t_list *tokens)
{
	if (syntax_error(tokens) == 1)
		return (1);
	return (0);
}

void	get_cmd_struct(t_parser *parser, char *token)
{
	t_list	*new_cmd;

	if (!parser->cmd_name)
		parser->cmd_name = ft_strdup(token);
	new_cmd = ft_lstnew(ft_strdup(token));
	ft_lstadd_back(&parser->cmd_list, new_cmd);
	parser->count++;
}

void	get_cmd(t_shell *shell, t_list **tokens_list)
{
	char		*token;
	char		*next_to_redir;
	t_list		*tokens;
	t_parser	*parser;

	tokens = *tokens_list;
	parser = init_parser();
	while (tokens && is_pipe_token(tokens->content) == 0)
	{
		token = tokens->content;
		if (is_redirects_token(token))
		{
			next_to_redir = tokens->next->content;
			get_redir_struct(shell, token, next_to_redir);
			tokens = tokens->next;
		}
		else
			get_cmd_struct(parser, token);
		tokens = tokens->next;
	}
	parser->cmd_args = get_cmd_arr(parser->cmd_list);
	ft_lstadd_back(&shell->commands, ft_lstnew(parser));
	*tokens_list = tokens;
}

void	parser(t_shell *shell)
{
	t_list	*tokens;

	if (shell->tokens && check_all_tokens(shell->tokens) == 0)
	{
		tokens = shell->tokens;
		while (tokens)
		{
			if (is_pipe_token(tokens->content) == 0)
				get_cmd(shell, &tokens);
			if (tokens)
				tokens = tokens->next;
		}
	}
	ft_lstclear(&shell->tokens, free);
	shell->tokens = NULL;
}
