/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:22:51 by vsivanat          #+#    #+#             */
/*   Updated: 2023/11/21 18:56:16 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# include <stdio.h>
#include "get_next_line.h"

char	*ft_trim_cache(char *cache)
{
	char	*result;
	int		newline;
	int		ind;

	newline = ft_strrchr_newline(cache);
	result = malloc(sizeof(char) * (newline + 2));
	ind = 0;
	while (ind < newline + 1)
	{
		result[ind] = cache[ind];
		ind++;
	}
	result[ind] = 0;
	free(cache);
	return (result);
}

char	*ft_trim_buffer(char *temp, int i)
{
	if (temp[i] == '\n')
	{
		while (i >= 0)
		{
			temp++;
			i--;
		}
	}
	return(temp);
}

char	*get_next_line(int fd)
{
	char		*cache;
	ssize_t		read_len;
	ssize_t		i;
	static char	*temp;
	static char	buffer[BUFFER_SIZE + 1];

	cache = NULL;
	if (fd < 0 || BUFFER_SIZE < 1 || read(fd, 0, 0) < 0)
		return (free(cache), NULL);
	read_len = 1;
	i = 0;
	while (read_len > 0)
	{
		i = ft_strrchr_newline(cache);
		if (i != -1)
			break;
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len <= 0)
			return (NULL);
		temp = ft_strjoin(cache, buffer);
		cache = temp;
	}
	cache = ft_trim_cache(cache);
	temp = ft_trim_buffer(temp, i);
	// printf("\n--------------------------%s\n", temp);
	return(cache);
}

# include <unistd.h>
# include <stdlib.h>
#include <fcntl.h>
int	main()
{
	int	fd;

	fd = open("hallo.txt", O_RDONLY);
	if (fd == -1)
	{
		perror("Error opening file");
		return 1;
	}
	// printf("%d", fd);
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	// printf("%s", get_next_line(fd));
	close(fd);
	return (0);
}
