/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vsivanat <vsivanat@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/05 12:22:51 by vsivanat          #+#    #+#             */
/*   Updated: 2023/11/26 14:04:26 by vsivanat         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


char	*ft_trim_cache(char *cache)
{
	char	*result;
	int		newline;
	int		ind;

	newline = ft_strlen(cache, 1);
	if (newline == -1)
		newline = ft_strlen(cache, 0);
	if (ft_strlen(cache, 0) == 0)
		newline = -1;
	result = malloc(sizeof(char) * (newline + 2));
	if (!result)
		return (NULL);
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

char	*next(char *temp)
{
	int		i;
	int		j;
	char	*line;

	i = 0;
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
	char		*cache;
	static int	ind = 0;
	ssize_t		read_len;
	static char	*temp;
	static char	buffer[BUFFER_SIZE + 1];

	cache = NULL;
	if (read(fd, 0, 0) < 0 || BUFFER_SIZE < 1 || fd < 0)
		return (free(cache), NULL);
	read_len = 1;
	while (read_len > 0)
	{
		cache = temp;
		if (ft_strlen(cache, 1) != -1)
			break ;
		read_len = read(fd, buffer, BUFFER_SIZE);
		if (read_len == 0 && ind++ == 0 && buffer[0] != 0)
			break ;
		if (read_len <= 0 || (ind > 1 && temp == NULL))
			return (free(temp), NULL);
		buffer[read_len] = 0;
		temp = ft_strjoin(cache, buffer);
	}
	temp = next(temp);
	return (ft_trim_cache(cache));
}

// # include <unistd.h>
// # include <stdlib.h>
// #include <fcntl.h>
// int	main()
// {
// 	int	fd;

// 	fd = open("hallo.txt", O_RDONLY);
// 	if (fd == -1)
// 	{
// 		perror("Error opening file");
// 		return 1;
// 	}
// 	// printf("%d", fd);
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	// printf("%s", get_next_line(fd));
// 	close(fd);
// 	return (0);
// }
