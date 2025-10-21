/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/04 16:24:23 by cczerwin          #+#    #+#             */
/*   Updated: 2025/01/04 16:24:25 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd);
void	*gnl_magic(char *line, char *buff, int fd, int *is_line);
void	*gnl_process(char *line, char *buff, int fd, int *is_line);
void	*gnl_newline(char *line, char *buff);
void	gnl_free(char *line, char *swap, char *buff);

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*line;
	int			is_line;

	line = NULL;
	is_line = 0;
	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	buff[BUFFER_SIZE] = 0;
	line = gnl_magic(line, buff, fd, &is_line);
	return (line);
}

void	*gnl_magic(char *line, char *buff, int fd, int *is_line)
{
	if (buff[0] != 0)
	{
		if (ft_strchr((char *)buff, '\n') != 0)
		{
			line = gnl_newline(line, buff);
			if (line == NULL)
				return (NULL);
			*is_line = 1;
		}
		else
			line = ft_strdup(buff);
	}
	while (*is_line == 0)
	{
		line = gnl_process(line, buff, fd, is_line);
		if (line == NULL)
		{
			gnl_free(line, NULL, buff);
			return (NULL);
		}
		if (*is_line != 1)
			buff[0] = 0;
	}
	return (line);
}

void	*gnl_process(char *line, char *buff, int fd, int *is_line)
{
	int	count;

	count = read(fd, buff, BUFFER_SIZE);
	if (count == -1)
	{
		gnl_free(line, NULL, buff);
		return (NULL);
	}
	buff[count] = 0;
	if (count == 0)
	{
		*is_line = 1;
		return (line);
	}
	if (line == NULL && ft_strchr(buff, '\n') == 0)
		line = ft_strdup(buff);
	else if (ft_strchr(buff, '\n') != 0)
	{
		line = gnl_newline(line, buff);
		*is_line = 1;
	}
	else
		line = gnl_strjoin(line, buff, 1);
	return (line);
}

void	*gnl_newline(char *line, char *buff)
{
	char	*swap;

	swap = ft_strchr((char *)buff, '\n');
	swap = ft_strdup(&swap[1]);
	if (swap == NULL)
	{
		gnl_free(line, swap, buff);
		return (NULL);
	}
	buff[ft_strchr(buff, '\n') - buff + 1] = 0;
	if (line == NULL)
		line = ft_strdup(buff);
	else
		line = gnl_strjoin(line, buff, 1);
	if (line == NULL)
	{
		gnl_free(line, swap, buff);
		return (NULL);
	}
	ft_memcpy(buff, swap, ft_strlen(swap));
	buff[ft_strlen(swap)] = 0;
	free (swap);
	return (line);
}

void	gnl_free(char *line, char *swap, char *buff)
{
	if (line != NULL)
		free (line);
	if (swap != NULL)
		free (swap);
	buff[0] = 0;
}
