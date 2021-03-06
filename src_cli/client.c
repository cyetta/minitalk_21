/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:16:54 by cyetta            #+#    #+#             */
/*   Updated: 2022/01/21 21:09:30 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

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

void	send_char(pid_t pid, char ch)
{
	int	i;

	i = 8;
	while (--i >= 0)
	{
		kill(pid, (ch >> i & 1) + SIGUSR1);
		usleep(400);
	}
	usleep(700);
}

void	send_str(int pid, char *str)
{
	int	i;

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
