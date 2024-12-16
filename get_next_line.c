/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hamr <yel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:04:19 by yel-hamr          #+#    #+#             */
/*   Updated: 2024/12/16 11:17:16 by yel-hamr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*allocate(int size)
{
	char	*str;

	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	str[size] = '\0';
	return (str);
}

char *line_to_return(char	*line)
{
	char	*ret;
	int		i;
	int		j;

	if(!line)
		return (NULL);
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	ret = malloc((i + 1) * sizeof(char));
	if (!ret)
		return (NULL);
	j = 0;
	while (j < i)
	{
		ret[j] = line[j];
		j++;
	}
	ret[j] = '\0';
	return (ret);
}

char *remaining_of_line(char *line)
{
	int		i;
	int		j;
	int		len;
	char	*str_temp;

	len = ft_strlen(line);
	if (!ft_strchr(line, '\n'))
	{
		free(line);
		return (NULL);
	}
	i = 0;
	while (line[i] && line[i] != '\n')
		i++;
	str_temp = malloc((len - i + 1) * sizeof(char));
	i++;
	j = 0;
	while (line[i + j])
	{
		str_temp[j] = line[i + j];
		j++;
	}
	str_temp[j] = '\0';
	free(line);
	return (str_temp);
}

char *get_next_line(int fd)
{
	static char		*line;
	char		*temp;
	char		*ret;
	int			read_return;

	temp = allocate((int)BUFFER_SIZE);
	read_return = 1;
	while (!ft_strchr(line, '\n') && read_return > 0)
	{
		read_return = read(fd, temp, BUFFER_SIZE);
		if (read_return == 0)
			break;
		if (read_return < 0)
		{
			free(temp);
            return (NULL);
		}
		line = ft_strjoin(line, temp);
	}
	ret = line_to_return(line);
	line = remaining_of_line(line);
	return (ret);
}

int main ()
{
	int i = 1;
    int fd = open("test.txt", O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
        return (0);
	
    char *s = get_next_line(fd);
    printf("return 1 is : %s\n", s);

	s = get_next_line(fd);
    printf("return 2 is : %s\n", s);
	
	s = get_next_line(fd);
    printf("return 3 is : %s\n", s);
    free(s);
}