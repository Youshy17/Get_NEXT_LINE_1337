/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hamr <yel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:04:19 by yel-hamr          #+#    #+#             */
/*   Updated: 2024/12/21 14:26:16 by yel-hamr         ###   ########.fr       */
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
	ret = malloc((i + 1) * sizeof(char));
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

char	*remaining_of_line(char *line)
{
	char	*remaining;
	int		len;
	int		i;
	int		j;

	len = ft_strlen(line);
	if (line == NULL)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	if (line[i] == '\0')
    {
        free(line);
        return (NULL);
    }
	remaining = malloc((len - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (line[i + j])
	{
		remaining[j] = line[i + j];
		j++;
	}
	remaining[j] = '\0';
	free(line);
	return (remaining);
}

char	*get_next_line(int fd)
{
	static char	*line;
	char		*temp;
	char		*ret;
	int			read_return;

	temp = malloc(sizeof(char) * ((int)BUFFER_SIZE + 1));
	if (!temp)
		return (NULL);
	temp[(int)BUFFER_SIZE] = '\0';
	read_return = 1;
	while (!ft_strchr(line, '\n') && read_return > 0)
	{
		read_return = read(fd, temp, BUFFER_SIZE);
		if (read_return == 0)
			break ;
		if (read_return < 0)
		{
			free(temp);
			return (NULL);
		}
		temp[read_return] = '\0';
		line = ft_strjoin(line, temp);
	}
	free(temp);
	ret = line_to_return(line);
	line = remaining_of_line(line);
	return (ret);
}

int	main(void)
{
	int fd = open("test.txt", O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
		return (0);

	char *s;
	int i = 0;
	while (i < 5)
	{
		s = get_next_line(fd);
		if (s)
			printf("line %d : %s",i ,s);
		else
			printf("line %d : %s\n",i ,s);
		i++;
	}
	
	free(s);
	close(fd);
}
