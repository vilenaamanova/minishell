/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshelba <oshelba@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/24 01:20:41 by ncathy            #+#    #+#             */
/*   Updated: 2022/09/24 15:28:01 by oshelba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_param_tty(t_shell *shell)
{
	tcgetattr(0, &(shell->setting_out_tty));
	tcgetattr(0, &(shell->setting_tty));
	(shell->setting_tty.c_lflag) &= ~ECHOCTL;
	tcsetattr(0, TCSANOW, &(shell->setting_tty));
}

void	unset_param_tty(t_shell *shell)
{
	tcsetattr(0, TCSANOW, &(shell->setting_out_tty));
}

void	sigint_handler(int num)
{
	int	retval;

	(void) num;
	retval = waitpid(-1, NULL, 0);
	if (retval == -1)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
	else
		write(1, "\n", 1);
}

void	sighandler_prepare(t_shell *shell)
{
	sigset_t	newset;

	sigemptyset(&newset); // sigemptyset инициализирует набор сигналов, указанный в set, и "очищает" его от всех сигналов.
	sigaddset(&newset, SIGINT); // int sigaddset(sigset_t *set, int signum); sigaddset и sigdelset добавляют сигналы signum к set и удаляют эти сигналы из набора соответственно.
	sigaddset(&newset, SIGQUIT);
	shell->s_int.sa_handler = sigint_handler;
	sigaction(SIGINT, &shell->s_int, NULL);
	signal(SIGQUIT, SIG_IGN);
}
