/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:22:51 by vsivanat          #+#    #+#             */
/*   Updated: 2023/12/12 20:13:19 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
