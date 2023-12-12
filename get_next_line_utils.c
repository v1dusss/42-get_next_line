/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:23:09 by vsivanat          #+#    #+#             */
/*   Updated: 2023/12/12 20:13:48 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str, char c)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	while (str[i] && str[i] != c)
		i++;
	if (str[i] == c)
		return (i);
	return (-1);
}

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		a;
	char	*result;

	if (!s2)
		return (NULL);
	if (!s1 || s1 == NULL)
	{
		s1 = malloc(sizeof(char) * 1);
		if (!s1)
			return (NULL);
		s1[0] = 0;
	}
	result = malloc((ft_strlen(s1, '\0') + ft_strlen(s2, '\0') + 1) * sizeof(char));
	if (!result)
		return (free(s1), NULL);
	i = -1;
	while (s1[++i] != '\0')
		result[i] = s1[i];
	a = 0;
	while (s2[a] != '\0')
		result[i++] = s2[a++];
	result[i] = '\0';
	return (free(s1), result);
}
