/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: esalmela <esalmela@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/04 12:12:15 by esalmela          #+#    #+#             */
/*   Updated: 2024/04/04 12:14:38 by esalmela         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

void	set_them_free(char *a, char *b)
{
	free(a);
	free(b);
}

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save[1000];

	if (fd < 0 || fd > 1000 || BUFFER_SIZE <= 0)
		return (NULL);
	save[fd] = read_line(fd, save[fd]);
	if (!save[fd])
		return (0);
	line = give_line(save[fd]);
	save[fd] = ft_save(save[fd]);
	if (ft_strlen(line) == 0)
	{
		set_them_free(save[fd], line);
		save[fd] = NULL;
		return (NULL);
	}
	return (line);
}

char	*read_line(int fd, char *save)
{
	char	*buff;
	int		bytes_read;

	if (ft_strchr(save, '\n'))
		return (save);
	buff = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buff)
	{
		free(save);
		return (NULL);
	}
	bytes_read = 1;
	while (!ft_strchr(save, '\n') && bytes_read > 0)
	{
		bytes_read = read(fd, buff, BUFFER_SIZE);
		if (bytes_read == -1)
		{
			set_them_free(save, buff);
			return (NULL);
		}
		buff[bytes_read] = '\0';
		save = ft_strjoin(save, buff);
	}
	free(buff);
	return (save);
}

char	*give_line(char *save)
{
	int		i;
	char	*line;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (save[i] == '\n')
		i++;
	line = malloc((i + 1) * sizeof(char));
	if (!line)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		line[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		line[i] = '\n';
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_save(char *save)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	str = malloc((ft_strlen(save) - i + 1) * sizeof(char));
	if (!str)
	{
		free(save);
		return (NULL);
	}
	i++;
	j = 0;
	while (save[i])
		str[j++] = save[i++];
	str[j] = '\0';
	free(save);
	return (str);
}
