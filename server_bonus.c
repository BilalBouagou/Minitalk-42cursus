/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouagou <bbouagou@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/13 07:57:42 by bbouagou          #+#    #+#             */
/*   Updated: 2023/02/14 15:50:52 by bbouagou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	reset_struct(t_info *info, pid_t si_pid)
{
	(*info).byte = 0;
	(*info).sigcount = 0;
	(*info).bytes_count = 0;
	fill_with_zeroes(&(*info));
	(*info).client_pid = si_pid;
}

static void	anti_norminette(t_info *info, int flag)
{
	if (flag == 1)
		(*info).byte *= 10;
	else if (flag == 0)
		(*info).flag += 1;
	else if (flag == 2)
	{
		(*info).byte *= 10;
		(*info).byte += 1;
	}
	else if (flag == 3)
	{
		(*info).sigcount = 0;
		(*info).byte = 0;
	}
}

static void	signal_handler(int signal, siginfo_t *siginfo, void	*context)
{
	static t_info	info;

	(void)context;
	if (info.client_pid != siginfo->si_pid)
		reset_struct(&info, siginfo->si_pid);
	info.sigcount++;
	if (SIGUSR1 == signal)
	{
		if (info.sigcount == info.flag + 1 && info.bytes_count == 0)
			anti_norminette(&(info), 0);
		anti_norminette(&(info), 2);
	}
	else
		anti_norminette(&(info), 1);
	if (info.sigcount == 8)
	{
		if (info.byte == 0)
			kill(siginfo->si_pid, SIGUSR2);
		else
		{
			info.byte = binary_to_decimal(ft_itoa(info.byte));
			detect_unicode(&info);
			anti_norminette(&(info), 3);
		}
	}
}

int	main(void)
{
	struct sigaction	sigact;

	ft_printf("Server's PID : %d\n", getpid());
	sigact.sa_sigaction = signal_handler;
	sigact.sa_flags = SA_SIGINFO;
	sigaction(SIGUSR1, &sigact, NULL);
	sigaction(SIGUSR2, &sigact, NULL);
	while (1)
		pause();
}
