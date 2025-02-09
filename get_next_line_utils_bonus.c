/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: youshy <youshy@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/02 10:45:53 by youshy            #+#    #+#             */
/*   Updated: 2025/02/09 11:52:14 by youshy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	count;

	if (s == NULL)
		return (0);
	count = 0;
	while (s[count])
		count++;
	return (count);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s1_len;
	int		s2_len;
	char	*ptr;
	int		i;
	int		ptr_count;

	s1_len = 0;
	s2_len = 0;
	if (s1)
		s1_len = ft_strlen(s1);
	if (s2)
		s2_len = ft_strlen(s2);
	ptr = malloc((s1_len + s2_len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	i = 0;
	ptr_count = 0;
	while (i < s1_len)
		ptr[ptr_count++] = s1[i++];
	i = 0;
	while (i < s2_len)
		ptr[ptr_count++] = s2[i++];
	ptr[ptr_count] = '\0';
	return (ptr);
}

char	*ft_strchr(const char *str, int c)
{
	unsigned char	cc;

	if (str == NULL)
		return (NULL);
	cc = (unsigned char)c;
	while (*str)
	{
		if ((unsigned char)*str == cc)
			return ((char *)(str));
		else
			str++;
	}
	if (cc == '\0' && *str == '\0')
		return ((char *)(str));
	else
		return (NULL);
}
