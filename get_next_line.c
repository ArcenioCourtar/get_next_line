/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:33:57 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/03 19:18:04 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc(), free(), size_t, NULL
#include <unistd.h> // read()
#include "get_next_line.h"

// fill buffer with '\0' before filling it up again.
static void	clear_buf(char *buffer)
{
	int	i;

	i = 0;
	while (i < BUFFER_SIZE)
	{
		buffer[i] = '\0';
		i++;
	}
}

static char	*found_nl(char *str, char *buffer)
{
	if (str == NULL)
	{
		str = create_str(buffer);
		move_buf(buffer);
		return (str);
	}
	str = concat_str(str, buffer);
	move_buf(buffer);
	return (str);
}

static char	*found_null(char *str, char *buffer)
{
	if (str == NULL)
	{
		str = create_str(buffer);
		clear_buf(buffer);
	}
	else
	{
		str = concat_str(str, buffer);
		clear_buf(buffer);
	}
	return (str);
}

// main loop. Goes through string in the opened filde descriptor.
// If it finds a newline, return whatever was found prior.
// In case it finds a '\0', store whatever was in the buffer previously
// And attempt to read() more lines from fd.
// Return if there's nothing more to read, or read() returns an error.
static char	*finder(char *str, char *buffer, int fd)
{
	int	loc;
	int	res;

	loc = 0;
	while (1)
	{
		if (buffer[loc] == '\n')
			return (found_nl(str, buffer));
		else if (buffer[loc] == '\0')
		{	
			loc = -1;
			str = found_null(str, buffer);
			res = read(fd, buffer, BUFFER_SIZE);
			if (str == NULL || res == 0)
				return (str);
			if (res < 0)
			{
				free(str);
				clear_buf(buffer);
				return (NULL);
			}
		}
		loc++;
	}
}

// Return line from fd when encountering a newline
char	*get_next_line(int fd)
{
	static char	buffer[BUFFER_SIZE + 1];
	char		*str;
	int			res;

	str = NULL;
	if (buffer[0] == '\0')
	{
		clear_buf(buffer);
		res = read(fd, buffer, BUFFER_SIZE);
		if (res == 0)
			return (NULL);
		if (res < 0)
		{
			clear_buf(buffer);
			return (NULL);
		}
	}
	return (finder(str, buffer, fd));
}
