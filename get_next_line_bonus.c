/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youshy <youshy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:45:47 by youshy            #+#    #+#             */
/*   Updated: 2025/02/09 18:21:48 by youshy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*line_to_return(char *line)
{
	char	*ret;
	int		i;
	int		j;

	if (!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	ret = malloc((i + 2) * sizeof(char));
	if (!ret)
		return (NULL);
	j = 0;
	while (j <= i)
	{
		ret[j] = line[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char	*remaining_of_line_bis(char *line, int len, int i)
{
	char	*remaining;
	int		j;

	remaining = malloc((len - i + 1) * sizeof(char));
	if (!remaining)
		return (NULL);
	j = 0;
	while (line[i + j])
	{
		remaining[j] = line[i + j];
		j++;
	}
	remaining[j] = '\0';
	return (remaining);
}

char	*remaining_of_line(char *line)
{
	char	*remaining;
	int		len;
	int		i;

	if (line == NULL)
		return (NULL);
	len = ft_strlen(line);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0' || line[i + 1] == '\0')
		return (free(line), line = NULL, NULL);
	i++;
	remaining = remaining_of_line_bis(line, len, i);
	return (free(line), line = NULL, remaining);
}

char	*get_next_line_bis(int fd, char **line)
{
	char	*temp;
	char	*t_line;
	int		read_return;

	temp = malloc(sizeof(char) * ((size_t)BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	read_return = 1;
	while (!ft_strchr(*line, '\n') && read_return > 0)
	{
		read_return = read(fd, temp, (size_t)BUFFER_SIZE);
		if (read_return == 0)
			break ;
		if (read_return < 0)
			return (free(temp), temp = NULL, free(*line), *line = NULL, NULL);
		temp[read_return] = '\0';
		t_line = *line;
		*line = ft_strjoin(*line, temp);
		free(t_line);
		t_line = NULL;
	}
	return (free(temp), temp = NULL, *line);
}

char	*get_next_line(int fd)
{
	static char	*line[1024];
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line[fd] = get_next_line_bis(fd, &line[fd]);
	if (!line[fd])
		return (NULL);
	ret = line_to_return(line[fd]);
	line[fd] = remaining_of_line(line[fd]);
	return (ret);
}
