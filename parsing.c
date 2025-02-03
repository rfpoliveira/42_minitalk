/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpedrosa <rpedrosa@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/08 12:40:09 by rpedrosa          #+#    #+#             */
/*   Updated: 2025/01/08 15:00:01 by rpedrosa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	parsing(int argc, char **argv)
{
	int	i;

	i = 0;
	if (argc != 3)
		return (-1);
	while (argv[1][i])
	{
		if (ft_isdigit(argv[1][i] == 0))
			return (-1);
		i++;
	}
	return (0);
}
