/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/25 19:03:45 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/05/28 22:25:39 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h> 

static void	*freeing(char **ptr)
{
	free(*ptr);
	*ptr = NULL;
	return (NULL);
}

char	*read_line(int fd, char *buffer, char *save)
{
	int		line_read;
	char	*line_saved;

	line_read = 1;
	while (line_read != 0)
	{
		line_read = read(fd, buffer, BUFFER_SIZE);
		if (line_read == -1)
			return (freeing(&save));
		else if (line_read == 0)
			break ;
		buffer[line_read] = '\0';
		if (!save)
		{
			save = ft_strdup("");
			if (!save)
				return (NULL);
		}
		line_saved = save;
		save = ft_strjoin(line_saved, buffer);
		freeing(&line_saved);
		if (!save)
			return (NULL);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	return (save);
}

char	*get_remaining(char *line)
{
	size_t	index;
	char	*remaining;

	index = 0;
	while (line[index] != '\n' && line[index] != '\0')
		index++;
	remaining = ft_substr(line, index + 1, ft_strlen(line) - index);
	if (!remaining)
		return (NULL);
	if (*remaining == '\0')
		freeing(&remaining);
	if (ft_strchr(line, '\n'))
		index++;
	line[index] = '\0';
	return (remaining);
}

char	*dup_line(char *line)
{
	char	*ret;
	size_t	line_len;

	line_len = 0;
	if (ft_strchr(line, '\n'))
	{
		line_len = ft_strchr(line, '\n') - line;
		line_len++;
	}
	else
		line_len = ft_strlen(line);
	ret = ft_substr(line, 0, line_len);
	freeing(&line);
	if (!ret)
		return (NULL);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buffer;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0 || read(fd, &buffer, 0) < 0)
	{
		if (save != NULL)
			freeing(&save);
		return (NULL);
	}
	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	line = read_line(fd, buffer, save);
	freeing(&buffer);
	if (!line)
		return (freeing(&save));
	save = get_remaining(line);
	line = dup_line(line);
	if (!line)
		return (freeing(&save));
	return (line);
}
/*int	main(int argc, char **argv)
{
	int fd;
	char *line;
	int lines;

	if (argc != 2)
		return (0);
//	printf("%d\n", getpid());
	lines = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		// printf("error opening the file");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("line no: %d -> %s\n", lines++, line);
		free(line);
	}
	close(fd);
	return (0);
}
*/
