/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_clear.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ncathy <ncathy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/28 11:50:23 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/28 19:56:42 by ncathy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	free_read_redir(t_redirread *read_struct)
{
	t_redirread	*next_read;

	while (read_struct)
	{
		next_read = read_struct->next;
		free (read_struct->file_name);
		free (read_struct->redir_operator);
		free (read_struct);
		read_struct = NULL;
		read_struct = next_read;
	}
}

void	free_write_redir(t_redirwrite *write_struct)
{
	t_redirwrite	*next_write;

	while (write_struct)
	{
		next_write = write_struct;
		free (write_struct->file_name);
		free (write_struct->redir_operator);
		free (write_struct);
		write_struct = NULL;
		write_struct = next_write;
	}
}

void	free_redirects(t_shell *shell)
{
	if (shell->redirects)
	{
		free (shell->redirects->operator);
		if (shell->redirects->redir_read)
			free_read_redir(shell->redirects->redir_read);
		else if (shell->redirects->redir_write)
			free_write_redir(shell->redirects->redir_write);
		free (shell->redirects);
	}	
}

void	free_parser_list(void *commands)
{
	t_parser	*parser;

	parser = (t_parser *)commands;
	free(parser->cmd_name);
	ft_lstclear(&parser->cmd_list, free);
	ft_split_free(parser->cmd_args);
	free(parser);
}

void	free_shell(t_shell *shell)
{
	t_envpmod	*next_node;

	while (shell->envp)
	{
		next_node = shell->envp->next;
		free (shell->envp->variable);
		free (shell->envp->value);
		free (shell->envp);
		shell->envp = NULL;
		shell->envp = next_node;
	}
	ft_split_free(shell->envp_arr);
	free(shell);
}
