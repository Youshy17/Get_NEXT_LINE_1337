/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youshy <youshy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:04:19 by yel-hamr          #+#    #+#             */
/*   Updated: 2025/02/09 11:50:22 by youshy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	i++;
	if (line[i] == '\0')
	{
		free(line);
		return (NULL);
	}
	remaining = remaining_of_line_bis(line, len, i);
	free(line);
	return (remaining);
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
		{
			free(temp);
			return (NULL);
		}
		temp[read_return] = '\0';
		t_line = *line;
		*line = ft_strjoin(*line, temp);
		free(t_line);
	}
	free(temp);
	return (*line);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*ret;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	line = get_next_line_bis(fd, &line);
	if (!line)
		return (NULL);
	ret = line_to_return(line);
	line = remaining_of_line(line);
	return (ret);
}
/*
int	main(void)
{
	char *s;
	s = get_next_line(1);
		if (s)
			printf("line %s" ,s);
		else
			printf("line %s\n",s);
	free(s);
}


int	main(void)
{
	int fd = open("test.txt", O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		return (0);

	char *s;
	int i = 0;
	while (i < 6)
	{
		s = get_next_line(fd);
		if (s)
			printf("line %d : %s",i ,s);
		else
			printf("line %d : %s\n",i ,s);
		i++;
		free(s);
	}
	
	close(fd);
}*/