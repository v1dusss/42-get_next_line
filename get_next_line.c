/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:22:51 by vsivanat          #+#    #+#             */
/*   Updated: 2024/12/19 18:49:48 by vsivanat         ###   ########.fr       */
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

char	*ft_trim_temp(char *temp, char **cache)
{
	int		newline;
	int		ind;
	char	*result;

	result = NULL;
	if (temp == NULL || ft_strlen(temp, '\0') == 0)
		return (free(temp), NULL);
	newline = ft_strlen(temp, '\n');
	if (newline == -1)
		return (temp);
	result = malloc(sizeof(char) * (newline + 2));
	if (!result)
		return (free(*cache), *cache = NULL, free(temp), temp = NULL, NULL);
	ind = -1;
	while (++ind < newline + 1)
		result[ind] = temp[ind];
	result[ind] = 0;
	free(temp);
	return (result);
}

char	*next(char *cache)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (cache == NULL)
		return (NULL);
	while (cache[i] && cache[i] != '\n')
		i++;
	if (!cache[i])
		return (NULL);
	line = malloc((ft_strlen(cache, '\0') - i + 1));
	if (!line)
		return (NULL);
	j = 0;
	while (cache[++i])
		line[j++] = cache[i];
	line[j++] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			read_len;
	char		*temp;
	static char	*cache;
	char		buffer[BUFFER_SIZE + 1];

	temp = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (free (cache), cache = NULL, free(temp), NULL);
	read_len = 1;
	temp = cache;
	while (read_len > 0 && ft_strlen(temp, '\n') == -1)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == 0 && cache == NULL)
			break ;
		if (read_len < 0)
			return (NULL);
		buffer[read_len] = 0;
		cache = ft_strjoin(cache, buffer);
		if (cache == NULL)
			return (NULL);
		temp = cache;
	}
	cache = next(cache);
	return (ft_trim_temp(temp, &cache));
}
