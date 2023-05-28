/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/10 03:26:10 by bbouagou          #+#    #+#             */
/*   Updated: 2023/01/18 20:58:41 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

sig_atomic_t	g_sigcount;

static void	signal_handler(int signal, siginfo_t *siginfo, void	*context)
{
	static int		byte;
	static pid_t	client_pid;

	(void)context;
	if (client_pid != siginfo->si_pid)
	{
		byte = 0;
		g_sigcount = 0;
		client_pid = siginfo->si_pid;
	}
	g_sigcount++;
	if (SIGUSR1 == signal)
	{
		byte *= 10;
		byte += 1;
	}
	else
		byte *= 10;
	if (g_sigcount == 8)
	{
		byte = binary_to_decimal(ft_itoa(byte));
		write(1, &byte, 1);
		g_sigcount = 0;
		byte = 0;
	}
}

int	main(void)
{
	struct sigaction	sigact;

	ft_printf("Server PID : %d\n", getpid());
	sigact.sa_sigaction = signal_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
}
