/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mucankir <mucankir@student.42kocaeli.co    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/14 21:51:05 by mucankir          #+#    #+#             */
/*   Updated: 2024/12/15 01:44:40 by mucankir         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>

char	*ft_new_static(char *static_str)
{
	int		i;
	int		j;
	char	*new_static;

	i = 0;
	while (static_str[i] && static_str[i] != '\n')
		i++;
	if (!static_str[i] && static_str)
	{
		free(static_str);
		return (static_str = NULL, NULL);
	}
	new_static = malloc(ft_strlen(static_str) - i + 1);
	if (!new_static)
	{
		free(static_str);
		return (static_str = NULL, NULL);
	}
	i++;
	j = 0;
	while (static_str[i] != '\0')
		new_static[j++] = static_str[i++];
	new_static[j] = '\0';
	free(static_str);
	return (new_static);
}

char	*ft_get_line(char *static_str)
{
	char	*line;
	int		i;

	i = 0;
	if (!static_str[i])
		return (NULL);
	while (static_str[i] != '\0' && static_str[i] != '\n')
		i++;
	line = malloc(i + 1 + ft_check_nl(static_str));
	if (!line)
		return (free(static_str), NULL);
	i = 0;
	while (static_str[i] != '\0' && static_str[i] != '\n')
	{
		line[i] = static_str[i];
		i++;
	}
	if (static_str[i] == '\n')
	{
		line[i] = static_str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_file_reader(char *static_str, int fd)
{
	char	*buffer;
	int		byte_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (free(static_str), NULL);
	byte_read = 1;
	while (!ft_check_nl(static_str) && byte_read != 0)
	{
		byte_read = read(fd, buffer, BUFFER_SIZE);
		if (byte_read == -1)
			return (free(static_str), free(buffer), NULL);
		buffer[byte_read] = '\0';
		static_str = ft_str_join(static_str, buffer);
	}
	free(buffer);
	return (static_str);
}

char	*get_next_line(int fd)
{
	static char	*static_str[4096];
	char		*current_line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free(static_str[fd]), NULL);
	static_str[fd] = ft_file_reader(static_str[fd], fd);
	if (!static_str[fd])
		return (NULL);
	current_line = ft_get_line(static_str[fd]);
	static_str[fd] = ft_new_static(static_str[fd]);
	return (current_line);
}
