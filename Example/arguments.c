/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arguments.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ugerkens <ugerkens@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 15:28:02 by ugerkens          #+#    #+#             */
/*   Updated: 2024/04/17 15:28:03 by ugerkens         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <philo.h>

t_status	check_arguments(int argc, char **argv)
{
	if (argc != 5 && argc != 6)
		return (ERROR_ARGUMENTS);
	while (--argc)
		if (!is_valid_positive_int(argv[argc]) || (argc == 5
				&& ft_atoi(argv[argc]) < 1) || (argc < 5 && argc > 1
				&& ft_atoi(argv[argc]) < MIN_TIME) || (argc == 1
				&& (ft_atoi(argv[argc]) > MAX_PHILOSOPHERS
					|| ft_atoi(argv[argc]) < 1)))
			return (ERROR_ARGUMENTS);
	return (SUCCESS);
}

bool	is_valid_positive_int(char *str)
{
	long	num;

	if (str == NULL || *str == '\0')
		return (false);
	if (*str == '0' && *(str + 1) != '\0')
		return (false);
	num = 0;
	while (*str != '\0')
	{
		if (!(*str >= '0' && *str <= '9'))
			return (false);
		num = num * 10 + (*str - '0');
		if (num > INT_MAX)
			return (false);
		str++;
	}
	return (true);
}

int	ft_atoi(const char *str)
{
	int	sign;
	int	value;

	sign = 1;
	value = 0;
	while (*str == ' ' || (*str >= '\t' && *str <= '\r'))
		str++;
	if (*str == '-' || *str == '+')
		sign = 44 - *str++;
	while (*str >= '0' && *str <= '9')
		value = value * 10 + (*str++ - '0');
	return (sign * value);
}
