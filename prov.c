#include "minishell.h"

	// t_envpmod *prov;
	// prov = shell->envp;
	// while (prov)
	// {
	// 	printf("%s\n", prov->variable);
	// 	printf("%s\n", prov->value);
	// 	prov = prov->next;
	// }

	// t_list *prov;
	// prov = shell->tokens;
	// while (prov)
	// {
	// 	printf("%s\n", (char *)prov->content);
	// 	prov = prov->next;
	// }

void find_builtin(t_shell *shell)
{
	t_parser	*parser;

	parser = (t_parser *)shell->commands->content;

	// printf("CMD LIST CONTENT IN FIND BUILTIN:\n");
	// printf("%s\n", (char *)parser->cmd_list->content);

	if (ft_strncmp("cd", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)))
		ft_cd(parser, shell);
	else if (ft_strncmp("pwd", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)))
		ft_pwd();
	else if (ft_strncmp("env", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)))
		env_pr(shell->envp);
	// if (ft_strncmp("export", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
	// 	ft_export(shell);
	// if (ft_strncmp("unset", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
	// 	delete_env(shell, shell->parser);
	else if (ft_strncmp("exit", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)))
		ft_exit(shell);
	else if (ft_strncmp("echo", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)))
		ft_echo(shell);
}

	// t_parser	*tmp;
	// tmp = (t_parser *)shell->commands->content;

	// t_parser	*tmp1;
	// t_parser	*tmp2;

	// tmp1 = (t_parser *)shell->commands->content;
	// tmp2 = (t_parser *)shell->commands->next->content;

	// int len_list = ft_lstsize(shell->commands);
	// printf("LEN CMD LIST: %d\n", len_list);
	// printf("%s\n", (char *)tmp->cmd_list->next->content);

	// printf("TMP1\n");
	// while (tmp1->cmd_list)
	// {
	// 	printf("%s\n", (char *)tmp1->cmd_list->content);
	// 	tmp1->cmd_list = tmp1->cmd_list->next;
	// }
	// printf("TMP2\n");
	// while (tmp2->cmd_list)
	// {
	// 	printf("%s\n", (char *)tmp2->cmd_list->content);
	// 	tmp2->cmd_list = tmp2->cmd_list->next;
	// }
	// while (tmp1)
	// {
	// 	printf("%s\n", (char *)tmp1->content->cmd_list->content);
	// 	tmp1 = tmp1->next;
	// }