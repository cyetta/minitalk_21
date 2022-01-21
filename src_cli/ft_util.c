/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_util.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cyetta <cyetta@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/21 18:44:54 by cyetta            #+#    #+#             */
/*   Updated: 2022/01/21 18:49:45 by cyetta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

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
