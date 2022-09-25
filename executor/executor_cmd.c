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
	if (!res)
		m_error(1, "");
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
  
void	pre_processor(t_shell *shell)
{
	int		num_pipe;
	int		pids;
	t_list	*list_commands;
	t_parser	*tmp;
	int **pipes;
	int i;

	tmp = shell->parser;
	i = -1;
	num_pipe = 1;
	while (tmp->next)
	{
		tmp = tmp->next;
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

int	builtins_cmd(t_shell *shell, t_parser *parser)
{
	int	code;
	int	save_fd;
	char *cmd;

	code = -42;
	save_fd = -1;
	
	if (cmd_list->content)
	{
		cmd = (char *)cmd_list->content;
		shell->status = 0;
		if (ft_strncmp("echo", cmd, ft_strlen(cmd) + 1) == 0)
			ft_echo(shell);
		if (ft_strncmp("pwd", cmd, ft_strlen(cmd) + 1) == 0)
			ft_pwd(shell);
		if (ft_strncmp("env", cmd, ft_strlen(cmd) + 1) == 0)
			env_pr(shell, parser);
		if (ft_strncmp("export", cmd, ft_strlen(cmd) + 1) == 0)
			return (cmd_list);
		if (ft_strncmp("unset", cmd, ft_strlen(cmd) + 1) == 0)
			return (&b_unset);
		if (ft_strncmp("exit", cmd, ft_strlen(cmd) + 1) == 0)
			return (&b_exit);
		if (ft_strncmp("cd", cmd, ft_strlen(cmd) + 1) == 0)
			return (&b_cd);
	}
}

void	executor(t_shell *shell)
{
	int			size_lst;
	int			code;
	t_parser	*cmd;
	int i;


	i = -1;
	if (hangle_error_code() || ft_lstsize(shell->parser->cmd_list) == 0)
		return ;
	pre_processor(shell);
	cmd = shell->parser;
	if (shell->pipes->num_pipe == 1)
		code = builtins_cmd(shell, cmd->cmd_list);
	while (cmd && ((shell->pipes->num_pipe) > 1 || code < 0))
	{
		shell->pipes->pids[++i] = fork();
		if (shell->pipes->pids[i] == 0)
		{
			code = builtins_cmd(shell, cmd->cmd_list);
			if (code < 0)
				run_cmd();
		}
		cmd->next;
	}
	post_process(shell);
}
