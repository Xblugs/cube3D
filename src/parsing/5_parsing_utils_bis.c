/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   5_parsing_utils_bis.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aeudes <aeudes@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/10 15:31:19 by aeudes            #+#    #+#             */
/*   Updated: 2025/12/22 16:44:11 by aeudes           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

bool	is_map_line(char *line)
{
	char	c;
	int		i;

	i = 0;
	while (line[i] && (line[i] == ' '))
		i++;
	c = line[i];
	return (c == '1' || c == '0' || c == 'N'
		|| c == 'S' || c == 'W' || c == 'E');
}

int	is_spawn(char c)
{
	return (c == 'N' || c == 'S' || c == 'W' || c == 'E');
}

/*
GNL LAISSE  "\n" A LA FIN DE LA CHAINE DE CARACTERE
CETTE FONCTION L'EFFACE 
*/

void	remove_newline(char *line)
{
	char	*temp;

	if (!line)
		return ;
	temp = ft_strchr(line, '\n');
	if (temp)
		*temp = '\0';
}
