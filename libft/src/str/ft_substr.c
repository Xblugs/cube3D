/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cczerwin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 17:30:36 by cczerwin          #+#    #+#             */
/*   Updated: 2024/10/23 17:30:40 by cczerwin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len);

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub;
	size_t	i;

	if (s == 0 || len == 0 || ft_strlen(s) <= start)
		return (ft_strdup(""));
	i = 0;
	if (len > ft_strlen(&s[start]))
		len = ft_strlen(&s[start]);
	if (s[start + 1] == 0)
		len = 1;
	sub = malloc((len + 1) * sizeof(char));
	if (sub == NULL)
		return (NULL);
	while (s[start + i] != 0 && i < len)
	{
		sub[i] = (char)s[start + i];
		i++;
	}
	sub[i] = 0;
	return (sub);
}
