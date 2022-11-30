/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 12:30:28 by acourtar          #+#    #+#             */
/*   Updated: 2022/11/30 16:00:08 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include "get_next_line.h"
#include <fcntl.h>

int	main(void)
{
	int fd = open("test_text.txt", O_RDONLY);
	char *str;
	int count = 1;

	printf("BUFFER_SIZE = %i\n", BUFFER_SIZE);
	str = get_next_line(fd);
	while (str)
	{
		printf("%i: ", count);
		printf("%s", str);
		free(str);
		str = get_next_line(fd);
		count++;
	}
	printf("%s", str);
	free(str);
}
