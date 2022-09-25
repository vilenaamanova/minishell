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

	printf("CMD LIST CONTENT IN FIND BUILTIN:\n");
	printf("%s\n", (char *)parser->cmd_list->content);

	if (ft_strncmp("cd", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)) == 0)
		ft_cd(shell);
	if (ft_strncmp("pwd", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)) == 0)
		ft_pwd();
	if (ft_strncmp("env", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		env_pr(shell, shell->envp);
	if (ft_strncmp("export", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		ft_export(shell);
	if (ft_strncmp("unset", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		delete_env(shell, shell->parser);
	if (ft_strncmp("exit", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		ft_exit(shell);
	if (ft_strncmp("echo", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		ft_echo(shell);
}