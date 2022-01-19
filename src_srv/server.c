/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/17 20:17:03 by cyetta            #+#    #+#             */
/*   Updated: 2022/01/20 02:51:40 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <signal.h>

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

int	main(void)
{
	write(1, "PID of this server is ", 22);
	ft_itoa(getpid());
	write(1, "\n", 1);
	return (0);
}
