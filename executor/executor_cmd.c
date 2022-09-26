#include "../minishell.h"

int	handle_error_code(t_shell *shell)
{
	if (shell->status < 0)
	{
		shell->status *= -1;
		return (1);
	}
	return (0);
}

int	**init_pipes(int pipes_amount)
{
	int	i;
	int	**res;

	i = 0;
	res = (int **)malloc(sizeof(int *) * (pipes_amount + 1));
	// if (!res)
	// 	m_error(1, "");
	while (i < pipes_amount)
	{
		res[i] = (int *)malloc(sizeof(int) * 2);
		if (!res[i])
			 ;//error 1
		if (pipe(res[i]) < 0)
			 ;//error 3
		i++;
	}
	return (res);
}
  
void	pre_processor(t_shell *shell, t_parser *tmp)
{
	int		num_pipe;
	int		*pids;
	// t_list	*list_commands;
	int **pipes;
	int i;

	i = -1;
	num_pipe = 1;
	while (tmp->cmd_list->next)
	{
		tmp = tmp->cmd_list->next;
		num_pipe++;
	}
	pids = (int *)malloc(sizeof(int) * num_pipe);
	if (!pids)
		 ;//error
	while (++i < num_pipe)
	{
		pids[i] = -1;
	}
	pipes = init_pipes(num_pipe);
	shell->pipes->pids = pids;
	shell->pipes->num_pipe = num_pipe;
	shell->pipes->pipes = pipes;
}

void	builtins_cmd(t_shell *shell, t_parser *parser)
{
	int	code;
	int	save_fd;
	char *cmd;

	code = -42;
	save_fd = -1;
	
	if (parser->cmd_list)
	{
		cmd = (char *)parser->cmd_list->content;
		shell->status = 0;
		// if (ft_strncmp("cd", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)) == 0)
		// 	ft_cd(parser, shell);
		if (ft_strncmp("pwd", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content)) == 0)
			ft_pwd();
		// if (ft_strncmp("env", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		// 	env_pr(shell->envp);
		// if (ft_strncmp("export", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		// 	ft_export(shell);
		// if (ft_strncmp("unset", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		// 	delete_env(shell, parser);
		// if (ft_strncmp("exit", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		// 	ft_exit(shell);
		// if (ft_strncmp("echo", (char *)parser->cmd_list->content, ft_strlen((char *)parser->cmd_list->content) + 1) == 0)
		// 	ft_echo(shell);
	}
}

void	executor(t_shell *shell)
{
	int			size_lst;
	int			code;
	t_parser	*cmd;
	int i;


	i = -1;
	cmd = (t_parser *)shell->commands->content;
	if (hangle_error_code() || ft_lstsize(cmd->cmd_list) == 0)
		return ;
	// pre_processor(shell, cmd);
	// if (shell->pipes->num_pipe == 0)
	// 	builtins_cmd(shell, cmd->cmd_list);
	// while (cmd && ((shell->pipes->num_pipe) > 0))
	// {
	// 	shell->pipes->pids[++i] = fork();
	// 	if (shell->pipes->pids[i] == 0)
	// 	{
	// 		builtins_cmd(shell, cmd->cmd_list); // code =
	// 		if (code < 0)
	// 			run_cmd();
	// 	}
	// 	cmd->cmd_list->next;
	// }
	// post_process(shell);
}
