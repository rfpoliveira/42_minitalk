/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:37:10 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/08 16:07:49 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	safe_kill(pid_t pid, int numb)
{
	int	i;

	i = 0;
	i = kill(pid, numb);
	if (i == -1)
	{
		ft_printf("Kill failed!\n");
		exit(1);
	}
	usleep(SLEEP);
}

void	send_str(char *str, pid_t pid)
{
	int		i;
	int		j;
	char	c;

	j = 0;
	while (str[j])
	{
		i = (sizeof(char) * 8) - 1;
		while (i >= 0)
		{
			c = str[j];
			if ((c >> i) & 1)
				safe_kill(pid, SIGUSR1);
			else
				safe_kill(pid, SIGUSR2);
			i--;
		}
		j++;
	}
	i = (sizeof(char) * 8) - 1;
	while (i-- >= 0)
		safe_kill(pid, SIGUSR2);
}

void	send_int(int n, pid_t pid)
{
	int	i;

	i = (sizeof(int) * 8) - 1;
	while (i >= 0)
	{
		if ((n >> i) & 1)
			safe_kill(pid, SIGUSR1);
		else
			safe_kill(pid, SIGUSR2);
		i--;
	}
}

int	main(int argc, char **argv)
{
	pid_t	pid;
	int		len;

	if (parsing(argc, argv) == -1)
	{
		ft_printf("Usage = ./client <PID> <MESSAGE>\n");
		exit (1);
	}
	pid = ft_atoi(argv[1]);
	if (kill(pid, 0))
	{
		ft_printf("PID Invalid\n");
		exit(1);
	}
	len = ft_strlen(argv[2]);
	send_int(len, pid);
	send_str(argv[2], pid);
}
