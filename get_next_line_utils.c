/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 10:45:30 by acourtar          #+#    #+#             */
/*   Updated: 2022/11/30 16:35:45 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h> // malloc(), size_t, NULL

// strlen but also stops counting at \n based on 'mode'
// mode = 1, regular strlen behaviour
// mode = 2, checks for \0 and \n. only used for gnl_strjoin()
size_t	gnl_strlen(const char *s, int mode)
{
	int	i;

	i = 0;
	if (mode == 1)
	{
		while (s[i] != '\0')
			i++;
	}
	else if (mode == 2)
	{
		while (s[i] != '\0' && s[i] != '\n')
			i++;
		if (s[i] == '\n')
			i++;
	}
	return (i);
}

char	*gnl_strdup(const char *s)
{
	char	*str;
	int		i;

	i = 0;
	if (s == NULL)
		return (NULL);
	str = malloc(gnl_strlen(s, 1) + 1);
	if (str == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		str[i] = s[i];
		i++;
	}
	str[i] = '\0';
	return (str);
}

// Modified strjoin that takes the buffer as second argument.
// Checks for \0 as well as \n when iterating over the buffer.
char	*gnl_strjoin(char const *s1, char const *s2)
{
	char	*str;
	int		i;
	int		j;

	i = 0;
	j = 0;
	str = malloc(gnl_strlen(s1, 1) + gnl_strlen(s2, 2) + 1);
	if (str == NULL)
		return (NULL);
	while (s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i] = s2[j];
		i++;
		j++;
		if (s2[j - 1] == '\n')
			break ;
	}
	str[i] = '\0';
	return (str);
}

void	*ft_memset(void *s, int c, size_t n)
{
	void			*ptr;
	unsigned char	c_uchar;

	ptr = s;
	c_uchar = (unsigned char)c;
	while (n > 0)
	{
		*(unsigned char *)ptr = c_uchar;
		n--;
		ptr++;
	}
	return (s);
}

char	*gnl_substr(char const *s, unsigned int start, size_t len)
{
	unsigned int	i;
	char			*str;
	unsigned int	const_len;

	i = 0;
	const_len = gnl_strlen(s, 1);
	if (start > const_len)
	{
		str = malloc(1);
		str[0] = '\0';
		return (str);
	}
	else if ((start + len) > const_len)
		str = malloc(const_len - start + 1);
	else
		str = malloc(len + 1);
	if (str == NULL)
		return (NULL);
	while (i < len && s[start + i] != '\0')
	{
		str[i] = s[start + i];
		i++;
	}
	str[i] = '\0';
	return (str);
}
