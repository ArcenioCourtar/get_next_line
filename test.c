/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:30:28 by acourtar          #+#    #+#             */
/*   Updated: 2023/03/29 17:30:22 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

int	main(void)
{
	int fd = open("test.c", O_RDONLY);
	char *str;

	str = get_next_line(fd);
	while (str)
	{
		write(1, str, strlen(str));
		free(str);
		str = get_next_line(fd);
	}
}
