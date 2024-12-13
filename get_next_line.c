/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yel-hamr <yel-hamr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/10 18:04:19 by yel-hamr          #+#    #+#             */
/*   Updated: 2024/12/13 14:29:04 by yel-hamr         ###   ########.fr       */
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

int	new_line_check(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\n')
		i++;
	if (str[i] == '\n')
		return (i);
	else
		return (0);
		
}

char *get_next_line(int fd)
{
	char		*line;
	static char	*temp;
	int			read_return;

	line = allocate(0);
	if (ft_strchr(temp, '\n'))
		line = ft_strjoin(line, ft_strchr(temp, '\n') + 1);
	else
		temp = allocate((int)BUFFER_SIZE);
	temp = allocate((int)BUFFER_SIZE);
	read_return = 1;
	while (read_return > 0)
	{
		read_return = read(fd, temp, BUFFER_SIZE);
		if (read_return = 0)
			break;
		if (read_return < 0)
			free(line); // free everything
		if (ft_strchr(temp, '\n') != NULL)
		{
			int i = 0;
			unsigned char c;
			while (temp[i] != '\n')
				i++;
			c = temp[i+1];
			temp[i+1] = '\0';
			line = ft_strjoin(line, temp);
			temp[i+1] = c;
			break;
		}
		else
			line = ft_strjoin(line, temp);
	}
	if (temp == NULL)
		free(temp);
	return (line);
}

int main ()
{
	int i = 1;
    int fd = open("test.txt", O_RDONLY | O_CREAT, 0644);
	if (fd == -1)
        return (0);
	
    char *s = get_next_line(fd);
    printf("%s", s);

	s = get_next_line(fd);
    printf("%s", s);
	
	printf("\n");

    free(s);
}