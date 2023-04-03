/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/03 14:08:15 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/03 19:17:54 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc(), free(), size_t, NULL
#include <unistd.h> // read()
#include "get_next_line.h"

// Modified strlen that also accounts for finding a newline in the buffer.
size_t	gnl_strlen(char *str)
{
	int	i;

	i = 0;
	while (1)
	{
		if (str[i] == '\0')
			return (i);
		if (str[i] == '\n')
			return (i + 1);
		i++;
	}
}

// Allocate memory and store whatever was in buffer, before the
// newline or '\0'
char	*create_str(char *buffer)
{
	char	*new;
	int		i;

	i = 0;
	new = malloc(gnl_strlen(buffer) + 1);
	if (new == NULL)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
	{
		new[i] = buffer[i];
		i++;
	}
	if (buffer[i] == '\n')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	return (new);
}

// norm compliance
static void	*concat_norm(char *new, char *buffer, int i)
{
	int	k;

	k = 0;
	while (buffer[k] != '\0' && buffer[k] != '\n')
	{
		new[i] = buffer[k];
		i++;
		k++;
	}
	if (buffer[k] == '\n')
	{
		new[i] = '\n';
		i++;
	}
	new[i] = '\0';
	return (new);
}

// If a string already exists from reading out previous buffer content,
// concatenate whatever is currently in the buffer.
char	*concat_str(char *old, char *buffer)
{
	char	*new;
	int		i;
	int		k;

	i = 0;
	k = 0;
	new = malloc(gnl_strlen(old) + gnl_strlen(buffer) + 1);
	if (new == NULL)
	{
		free(old);
		return (NULL);
	}
	while (old[i] != '\0')
	{
		new[i] = old[i];
		i++;
	}
	free(old);
	concat_norm(new, buffer, i);
	return (new);
}

// Shift the buffer content so that whatever has been read is overwritten
// with all the content that hasn't been read yet.
void	move_buf(char *buffer)
{
	int	len;
	int	i;

	len = gnl_strlen(buffer);
	i = 0;
	while (i + len < BUFFER_SIZE)
	{
		buffer[i] = buffer[i + len];
		i++;
	}
	buffer[i] = '\0';
}
