/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:45:27 by acourtar          #+#    #+#             */
/*   Updated: 2022/11/30 16:38:23 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc(), free(), size_t, NULL
#include <unistd.h> // read()
#include "get_next_line.h" // BUFFER_SIZE

size_t	gnl_strlen(const char *s, int mode);
char	*gnl_strdup(const char *s);
char	*gnl_strjoin(char const *s1, char const *s2);
void	*ft_memset(void *s, int c, size_t n);
char	*gnl_substr(char const *s, unsigned int start, size_t len);

// frees the passed pointer and returns NULL
// this function is only called when a malloc error happens in cat_buf
static char	*exit_func(char *str)
{
	free(str);
	return (NULL);
}

// Either puts the contents of 'buf' in 'str' or
// Concatenates the current contents of 'str' and 'buf'
// Returning a new string 'str' in the process
// sets *start to 0. #lineissues
static char	*cat_buf(char *str, char *buf, int count, int *start)
{
	char	*tmp1;

	if (str == NULL)
	{
		str = gnl_substr(buf, *start, count - *start);
		if (str == NULL)
			return (exit_func(str));
		return (str);
	}
	tmp1 = gnl_strdup(str);
	free(str);
	if (tmp1 == NULL)
		return (exit_func(tmp1));
	str = gnl_strjoin(tmp1, buf);
	free(tmp1);
	if (str == NULL)
		return (exit_func(str));
	*start = 0;
	return (str);
}

// Clears the entire buffer and places new content inside of the buffer.
// Returns an int to announce if the read() call succeeded or not.
// 1 = read succeeded. 0 = reached EOF, but *str has content.
// -1 = an error occured, or reached EOF, while *str is empty.
// Using a reference to str to modify it without having to return it.
// Sets *count to -1 since I increment count startig the while loop.
static int	reading(int fd, char **str, char *buf, int *count)
{
	int	result;

	ft_memset(buf, '\0', BUFFER_SIZE);
	result = read(fd, buf, BUFFER_SIZE);
	if (result == 0)
	{
		if (*str[0] == '\0')
		{
			free(*str);
			*str = NULL;
			return (-1);
		}
		return (0);
	}
	if (result < 0)
	{
		free(*str);
		*str = NULL;
		return (-1);
	}
	*count = -1;
	return (1);
}

// Reads target fd until it encounters the first newline, or EOF.
// If reading succeeds, returns the appropriate string.
// On error, or if EOF was already reached during the last call, returns NULL
char	*get_next_line(int fd)
{
	static char	buf[BUFFER_SIZE + 1];
	static int	count = -1;
	char		*str;
	int			start;

	start = count + 1;
	str = NULL;
	while (1)
	{
		count++;
		if (count >= BUFFER_SIZE || buf[0] == '\0')
		{
			str = cat_buf(str, buf, count, &start);
			if (str == NULL)
				return (NULL);
			if (reading(fd, &str, buf, &count) <= 0)
				return (str);
		}
		else if (buf[count] == '\n')
		{
			str = cat_buf(str, buf, count + 1, &start);
			return (str);
		}
	}
	return (str);
}
