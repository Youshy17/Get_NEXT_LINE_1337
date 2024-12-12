/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hamr <yel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:04:19 by yel-hamr          #+#    #+#             */
/*   Updated: 2024/12/12 12:56:29 by yel-hamr         ###   ########.fr       */
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

char *get_next_line(int fd)
{
	char	*temp;
	char	*line;
	int		read_return;
	
	temp = allocate((int)BUFFER_SIZE);
	line = allocate(0);
	read_return = 1;
	while (read_return > 0)
	{
		read_return = read(fd, temp, BUFFER_SIZE);
		temp[BUFFER_SIZE] = '\0';
		line = ft_strjoin(line, temp);
	}
	free(temp);
	return (line);
}

int main ()
{
	int i = 1;
    int fd = open("get_next_line.c", O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
        return (0);
    char *s = get_next_line(fd);
    printf("%s", s);
    free(s);
}