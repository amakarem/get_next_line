/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aelaaser <aelaaser@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/23 18:27:21 by aelaaser          #+#    #+#             */
/*   Updated: 2024/12/16 22:27:59 by aelaaser         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

static char	*free_and_return_null(char *buffer, char *str)
{
	free(buffer);
	free(str);
	return (NULL);
}

// static char	*read_fd_to_str_bybit(int fd)
// {
// 	char	*buffer;
// 	char	*str;
// 	char	ch;
// 	ssize_t	bytes;

// 	buffer = (char *)malloc(BUFFER_SIZE + 1);
// 	str = (char *)malloc(1);
// 	if (!str || !buffer)
// 		return (free_and_return_null(buffer, str));
// 	str[0] = '\0';
// 	bytes = 1;
// 	while (bytes > 0)
// 	{
// 		bytes = read(fd, buffer, 1);
// 		if (bytes == -1)
// 			return (free_and_return_null(buffer, str));
// 		if (bytes != 0)
// 		{
// 			buffer[bytes] = '\0';
// 			ch = buffer[0];
// 			str = ft_strjoin(str, buffer);
// 			if (!str)
// 				return (free_and_return_null(buffer, str));
// 			if (ch == '\n')
// 				bytes = 0;
// 		}
// 	}
// 	if (ft_strlen(str) == 0)
// 		return (free_and_return_null(buffer, str));
// 	free(buffer);
// 	return (str);
// }

static char	*read_fd_to_str(int fd, char *str)
{
	char	*buffer;
	int		bytes;
	char	*tmp;

	buffer = (char *)malloc(sizeof(char) * BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes = 1;
	while (!(ft_strchr(str, '\n')) && bytes != 0)
	{
		bytes = read(fd, buffer, BUFFER_SIZE);
		if (bytes == -1)
			return (free_and_return_null(buffer, str));
		buffer[bytes] = '\0';
		tmp = ft_strjoin(str, buffer);
		if (!tmp)
			return (free_and_return_null(buffer, str));
		free(str);
		str = tmp;
	}
	free(buffer);
	return (str);
}

static char	*get_one_line(char *str)
{
	char	*line;
	int		i;

	i = 0;
	if (!str[i])
		return (NULL);
	line = malloc(sizeof(char) * ft_strlen(str) + 1);
	if (!line)
		return (free_and_return_null(str, line));
	while (str[i] && str[i] != '\n')
	{
		line[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
	{
		line[i] = str[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

static char	*start_next_line(char *str)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (!str[i])
	{
		free(str);
		return (NULL);
	}
	new_str = (char *)malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!new_str)
		return (NULL);
	i++;
	j = 0;
	while (str[i] != '\0')
	{
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = read_fd_to_str(fd, str[fd]);
	if (!str[fd])
		return (NULL);
	line = get_one_line(str[fd]);
	str[fd] = start_next_line(str[fd]);
	return (line);
}
