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

t_parser	*init_parser(t_parser *parser)
{
	parser = (t_parser *)malloc(sizeof(t_parser));
	if (!parser)
		return (NULL);
	parser->cmd_list = NULL;
	parser->cmd_name = NULL;
	parser->count = 0;
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

	if (parser->cmd_name == NULL)
		parser->cmd_name = ft_strdup(token);
	new_cmd = ft_lstnew(parser->cmd_name);
	ft_lstadd_back(&parser->cmd_list, new_cmd);
	parser->count++;
}

void	get_cmd(t_shell *shell, t_list *tokens)
{
	t_parser	*parser;
	char		*token;
	char		*next_to_redir;

	init_parser(shell->parser);
	parser = shell->parser;
	while (tokens && is_pipe_token(tokens->content) != 1)
	{
		token = tokens->content;
		if (is_redirects_token(token))
		{
			next_to_redir = tokens->next->content;
			get_redir_struct(shell, token, next_to_redir);
		}
		else
			get_cmd_struct(parser, token);
		tokens = tokens->next;
	}
}

void	parser(t_shell *shell)
{
	t_list	*tokens;

	if (check_all_tokens(shell->tokens) == 0)
	{
		tokens = shell->tokens;
		if (tokens) // проверяем сущ-ет ли список и пайпы
		{
			while (tokens)
			{
				if (is_pipe_token(tokens->content) == 0)
					get_cmd(shell, tokens);
				tokens = tokens->next;
			}
		}
	}
	// очищаем список токенов в самом главном списке
}
