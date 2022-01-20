/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:16:54 by cyetta            #+#    #+#             */
/*   Updated: 2022/01/21 00:16:36 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

volatile int	g_ack_flag = 0;

int	ft_atoi(char *s)
{
	unsigned int	val;
	int				sign;

	val = 0;
	sign = 1;
	if (*s != '-' && (*s < '0' || *s > '9'))
		return (val);
	else if (*s == '-')
		sign = -1;
	else
		s--;
	while (*(++s) && *s >= '0' && *s <= '9')
		val = val * 10 + (*s - '0');
	return ((int)val * sign);
}

void	sighandler(int signal, siginfo_t *siginfo, void *context)
{
	(void)siginfo;
	(void)context;
	if (signal == SIGUSR1)
		g_ack_flag = 0;
}

void	send_char(pid_t pid, char ch)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		g_ack_flag = 1;
		kill(pid, (ch >> i & 1) + SIGUSR1);
		usleep(100);
		// while (g_ack_flag)
		// {
		// 	usleep(100);
		// 	// kill(pid, (ch >> i & 1) + SIGUSR1);
		// }
	}
}

void	send_str(int pid, char *str)
{
	struct sigaction	s_act;
	int					i;

	s_act.sa_flags = SA_SIGINFO;
	s_act.sa_sigaction = sighandler;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	i = -1;
	while (str[++i])
		send_char(pid, str[i]);
	send_char(pid, str[i]);
}

int	main(int argc, char **argv)
{
	int		pid;

	if (argc != 3)
	{
		write(2, "Incorrect parameters, usage: client <server_PID> <\"ascii \
string\"> \n", 67);
		return (1);
	}
	pid = ft_atoi(argv[1]);
	if (pid <= 0)
	{
		write(2, "Incorrect parameters, usage: client <server_PID> <\"ascii \
string\"> \n", 67);
		return (1);
	}
	send_str(pid, argv[2]);
	return (0);
}
