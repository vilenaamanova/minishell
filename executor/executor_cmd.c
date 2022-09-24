#include "../minishell.h"

int	executor(t_shell *shell)
{
	int size_lst;
	

	size_lst = ft_lstsize(shell->parser->cmd_list);
	if (size_lst == 1)
	{
		
	}
	return 1;
}