/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:17:03 by cyetta            #+#    #+#             */
/*   Updated: 2022/01/21 17:05:07 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

typedef struct s_symb
{
	int		prnt_flg;
	char	ch;
}	t_symb;

t_symb	g_symb;

void	ft_itoa(int a)
{
	unsigned int	n;
	char			ch;

	if (a < 0)
	{
		write(1, "-", 1);
		n = -a;
	}
	else
		n = a;
	if (a == 0)
		write(1, "0", 1);
	else
	{
		if (n / 10)
			ft_itoa(n / 10);
		ch = '0' + n % 10;
		write(1, &ch, 1);
	}
}

void	sighandler(int signal, siginfo_t *siginfo, void *context)
{
	static int	a = 8;
	static char	sym = 0;
	static int	pid = 0;

	(void)context;
	if (siginfo->si_pid != pid)
	{
		a = 8;
		sym = 0;
		pid = siginfo->si_pid;
	}
	sym = (sym << 1) | (signal - SIGUSR1);
	if (!--a)
	{
		g_symb.ch = sym;
		g_symb.prnt_flg = 1;
		a = 8;
	}
}

int	main(void)
{
	struct sigaction	s_act;

	write(1, "Server PID: ", 12);
	ft_itoa(getpid());
	write(1, "\n", 1);
	s_act.sa_flags = SA_SIGINFO;
	s_act.sa_sigaction = sighandler;
	sigaction(SIGUSR1, &s_act, NULL);
	sigaction(SIGUSR2, &s_act, NULL);
	while (1)
	{
		if (g_symb.prnt_flg)
		{
			if (g_symb.ch)
				write(1, &(g_symb.ch), 1);
			else
				write(1, "\n", 1);
			g_symb.prnt_flg = 0;
		}
		pause();
	}
	return (0);
}
