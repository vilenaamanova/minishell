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
		}
		else
			get_cmd_struct(parser, token);
		tokens = tokens->next;
	}
	ft_lstadd_back(&shell->commands, ft_lstnew(parser));
	*tokens_list = tokens;

	// t_list	*tmp;
	// tmp = parser->cmd_list;
	// printf("CMD LIST:\n");
	// while (tmp)
	// {
	// 	printf("%s\n", (char *)tmp->content);
	// 	tmp = tmp->next;
	// }
	
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

	// t_parser	*tmp;
	// int			len_list;

	// len_list = 0;
	// tmp = (t_parser *)shell->commands->content;
	// len_list = ft_lstsize(shell->commands);
	// printf("LEN CMD LIST: %d\n", len_list);

	t_list		*tmp_list;
	t_parser	*tmp_parser;

	tmp_list = shell->commands;
	printf("hello\n");
	while (tmp_list)
	{
		tmp_parser = (t_parser *)tmp_list->content;
		printf("kjajdsf%s\n", (char *)tmp_parser->cmd_list->content);
		tmp_list = tmp_list->next;
	}

	// t_parser	*tmp;
	// tmp = (t_parser *)shell->commands->content;
	// printf("CMD LIST:\n");
	// while (tmp->cmd_list)
	// {
	// 	printf("%s\n", (char *)tmp->cmd_list->content);
	// 	tmp->cmd_list = tmp->cmd_list->next;
	// }

	ft_lstclear(&shell->tokens, free);
	shell->tokens = NULL;
}
