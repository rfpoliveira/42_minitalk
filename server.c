/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 15:24:36 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/08 16:07:54 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	alloc_memory(t_data *data)
{
	data->int_received = 1;
	data->mensage = ft_calloc(data->info + 1, sizeof(char));
	if (!data->mensage)
	{
		ft_printf("ft_calloc failed!\n");
		exit(1);
	}
	data->mensage[data->info] = '\0';
	data->bits = 0;
	data->info = 0;
}

static void	handle_mensage(t_data *data)
{
	static int	i;

	data->mensage[i] = data->info;
	i++;
	data->bits = 0;
	if (data->info == 0)
	{
		ft_printf("%s\n", data->mensage);
		free(data->mensage);
		data->mensage = NULL;
		i = 0;
		data->int_received = 0;
	}
	data->info = 0;
}

void	handler(int numb)
{
	static t_data	data;

	if (numb == SIGUSR1 && data.int_received)
		data.info |= 1 << (7 - data.bits);
	else if (numb == SIGUSR2 && data.int_received)
		data.info &= ~(1 << (7 - data.bits));
	else if (numb == SIGUSR1 && !data.int_received)
		data.info |= 1 << (31 - data.bits);
	else if (numb == SIGUSR2 && !data.int_received)
		data.info &= ~(1 << (31 - data.bits));
	data.bits++;
	if (data.bits == (sizeof(int) * 8) && data.int_received == 0)
		alloc_memory(&data);
	if ((data.bits == 8) && data.int_received == 1)
		handle_mensage(&data);
}

int	main(void)
{
	struct sigaction	action;
	pid_t				pid;

	pid = getpid();
	if (pid == -1)
	{
		ft_printf("PID Invalid\n");
		exit (1);
	}
	ft_printf("The PID is: %d\n", getpid());
	sigemptyset(&action.sa_mask);
	action.sa_handler = handler;
	action.sa_flags = 0;
	sigaction(SIGUSR1, &action, NULL);
	sigaction(SIGUSR2, &action, NULL);
	while (42)
		pause();
}
