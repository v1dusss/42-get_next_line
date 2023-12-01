/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:22:51 by vsivanat          #+#    #+#             */
/*   Updated: 2023/12/01 19:26:55 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_trim_cache(char *cache, char **temp)
{
	int		newline;
	int		ind;
	char	*result;

	result = NULL;
	if (cache == NULL || ft_strlen(cache, 0) == 0)
		return (free(cache), NULL);
	newline = ft_strlen(cache, 1);
	if (newline == -1)
		newline = ft_strlen(cache, 0) - 1;
	if (ft_strlen(cache, 0) == 0)
		newline = -1;
	result = malloc(sizeof(char) * (newline + 2));
	if (!result)
		return (free(*temp), *temp = NULL, free(cache), cache = NULL, NULL);
	ind = -1;
	while (++ind < newline + 1)
		result[ind] = cache[ind];
	result[ind] = 0;
	free(cache);
	return (result);
}

char	*next(char *temp)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
	if (temp == NULL)
		return (NULL);
	while (temp[i] && temp[i] != '\n')
		i++;
	if (!temp[i])
		return (NULL);
	line = malloc((ft_strlen(temp, 0) - i + 1));
	if (!line)
		return (NULL);
	i++;
	j = 0;
	while (temp[i])
		line[j++] = temp[i++];
	line[j++] = '\0';
	return (line);
}

char	*get_next_line(int fd)
{
	int			read_len;
	char		*cache;
	static char	*temp;
	static char	buffer[BUFFER_SIZE + 1];

	cache = NULL;
	if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
		return (free (temp), temp = NULL, free(cache), NULL);
	read_len = 1;
	cache = temp;
	while (read_len > 0 && ft_strlen(cache, 1) == -1)
	{
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == 0 && buffer[0] != 0 && temp == NULL)
			break ;
		if (read_len < 0)
			return (NULL);
		buffer[read_len] = 0;
		temp = ft_strjoin(cache, buffer);
		if (temp == NULL)
			return (NULL);
		cache = temp;
	}
	temp = next(temp);
	return (ft_trim_cache(cache, &temp));
}

// # include <unistd.h>
// # include <stdlib.h>
// # include <stdio.h>
// #include <fcntl.h>
// int	main()
// {
// 	int	fd;

// 	fd = open("test.txt", O_RDWR);
// 	if (fd == -1)
// 	{
// 		// perror("Error opening file");
// 		return 1;
// 	}
// 	// printf("%d", fd);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
