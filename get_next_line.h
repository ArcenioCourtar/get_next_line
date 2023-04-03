/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acourtar <acourtar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/16 13:32:40 by acourtar          #+#    #+#             */
/*   Updated: 2023/04/03 19:18:24 by acourtar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 100
# endif
# include <stdlib.h>

// Reads file 'fd' and returns everything before the next newline it encounters
char	*get_next_line(int fd);
char	*create_str(char *buffer);
char	*concat_str(char *old, char *buffer);

size_t	gnl_strlen(char *str);

void	move_buf(char *buffer);

#endif