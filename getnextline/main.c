/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hskrzypi <hskrzypi@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/01 13:06:13 by hskrzypi          #+#    #+#             */
/*   Updated: 2024/06/01 13:06:36 by hskrzypi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>

int	main(int argc, char **argv)
{
	int fd;
	char *line;
	int lines;

	if (argc != 2)
	{
		printf("choose a file to read");	
		return (0);
	}
	lines = 1;
	fd = open(argv[1], O_RDONLY);
	if (fd == -1)
	{
		printf("error opening the file");
		return (1);
	}
	while ((line = get_next_line(fd)))
	{
		printf("%s", line);
		free(line);
	}
	close(fd);
	return (0);
}
