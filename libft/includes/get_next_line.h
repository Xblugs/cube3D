/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:24:47 by cczerwin          #+#    #+#             */
/*   Updated: 2025/01/04 16:24:49 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdio.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 25
# endif

///////////		get_next_line			///////////

char	*get_next_line(int fd);
void	*gnl_magic(char *line, char *buff, int fd, int *is_line);
void	*gnl_process(char *line, char *buff, int fd, int *is_line);
void	*gnl_newline(char *line, char *buff);
void	gnl_free(char *line, char *swap, char *buff);

///////////		get_next_line_utils		///////////

size_t	ft_strlen(const char *s);
char	*ft_strchr(const char *s, int c);
char	*ft_strdup(const char *src);
char	*gnl_strjoin(char *s1, char *s2, int to_free);
void	*ft_memcpy(void *dest, const void *src, size_t n);

#endif
