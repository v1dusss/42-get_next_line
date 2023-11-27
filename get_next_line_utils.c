/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:23:09 by vsivanat          #+#    #+#             */
/*   Updated: 2023/11/27 14:28:01 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str, int nb)
{
	int	c;

	c = 0;
	if (nb == 0)
	{
		while (str[c] != '\0')
			c++;
		return (c);
	}
	else
	{
		if (!str)
			return (-1);
		while (str[c] != '\n' && str[c] != '\0')
			c++;
		if (str[c] == '\n')
			return (c);
		return (-1);
	}
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	a;
	char	*result;

	if (!s2)
		return (NULL);
	if (!s1)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	result = malloc((ft_strlen(s1, 0) + ft_strlen(s2, 0) + 1) * sizeof(char));
	if (!result)
		return (NULL);
	i = -1;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	a = 0;
	while (s2[a] != '\0')
		result[i++] = s2[a++];
	result[i] = '\0';
	free(s1);
	return (result);
}

// int	ft_strrchr_newline(char *s)
// {
// 	int	c;

// 	if (!s)
// 		return (-1);
// 	c = 0;
// 	while (s[c] != '\n' && s[c] != '\0')
// 		c++;
// 	if (s[c] == '\n')
// 		return (c);
// 	return (-1);
// }
