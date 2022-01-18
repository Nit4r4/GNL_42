/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vferraro <marvin@42lausanne.ch>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/28 12:23:27 by vferraro          #+#    #+#             */
/*   Updated: 2022/01/18 11:47:42 by vferraro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

void	get_next(int fd, char *buff, char **fd_line)
{
	int		read_line;
	char	*stock;

	read_line = read(fd, buff, BUFFER_SIZE);
	while (read_line > 0)
	{
		buff[read_line] = '\0';
		if (!*fd_line)
			*fd_line = ft_substr(buff, 0, read_line);
		else
		{
			stock = *fd_line;
			*fd_line = ft_strjoin(*fd_line, buff);
			free(stock);
		}
		if (ft_strchr(buff, '\n'))
			break ;
		read_line = read(fd, buff, BUFFER_SIZE);
	}
	free(buff);
}

char	*line(char **fd_line)
{
	int		i;
	int		j;
	char	*ret;
	char	*stock;

	if (!*fd_line)
		return (NULL);
	if (!ft_strchr(*fd_line, '\n'))
	{
		ret = ft_substr(*fd_line, 0, ft_strlen(*fd_line));
		free(*fd_line);
		*fd_line = 0;
		if (ret[0] == '\0')
			free (ret);
		if (ret[0] != '\0')
			return (ret);
		return (NULL);
	}
	i = ft_strlen(*fd_line);
	j = ft_strlen(ft_strchr(*fd_line, '\n'));
	ret = ft_substr(*fd_line, 0, i - j + 1);
	stock = *fd_line;
	*fd_line = ft_substr(ft_strchr(*fd_line, '\n'), 1, j);
	free(stock);
	return (ret);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	static char	*fd_line;

	buffer = malloc(BUFFER_SIZE + 1);
	if (fd < 0 || !buffer || BUFFER_SIZE <= 0)
	{
		free(buffer);
		return (NULL);
	}
	get_next(fd, buffer, &fd_line);
	return (line(&fd_line));
}
