/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:57:45 by bbouagou          #+#    #+#             */
/*   Updated: 2023/02/14 18:30:21 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

pid_t	g_server_pid;

static void	signal_handler(int signal, siginfo_t *siginfo, void	*context)
{
	(void)context;
	(void)signal;
	if (siginfo->si_pid == g_server_pid)
		write(1, "\n\n\t\tSTRING HAS BEEN WELL RECEIVED !\t\t\n\n", 36);
}

static void	send_byte(char character)
{
	int			kill_status;
	int			j;

	j = 7;
	while (j >= 0)
	{
		if (character & (1 << j))
			kill_status = kill(g_server_pid, SIGUSR1);
		else
			kill_status = kill(g_server_pid, SIGUSR2);
		if (kill_status < 0)
		{
			write(1, "\n\nError, something went wrong with kill.\n\n", 42);
			exit(-1);
		}
		usleep(100);
		j--;
	}
}

int	main(int argc, char **argv)
{
	size_t				i;
	struct sigaction	sigact;

	if (argc == 3)
	{
		i = -1;
		g_server_pid = ft_atoi(argv[1]);
		if (g_server_pid <= 1)
		{
			write(1, "Make sure you have entered a valid PID.\n", 40);
			exit(0);
		}
		sigact.sa_sigaction = signal_handler;
		sigact.sa_flags = SA_SIGINFO;
		sigaction(SIGUSR2, &sigact, NULL);
		while (++i < ft_strlen(argv[2]) + 1)
			send_byte(argv[2][i]);
	}
	else
		write(1, "Incorrect number of arguments.\n", 31);
	return (0);
}
