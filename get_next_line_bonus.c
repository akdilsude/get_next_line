/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sakdil <sakdil@student.42istanbul.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/29 16:22:30 by sakdil            #+#    #+#             */
/*   Updated: 2024/11/30 16:56:41 by sakdil           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int	newline(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
	{	
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_read(char *str, int fd)
{
	char	*temp;
	int		index;

	temp = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	index = 1;
	while (!newline(str) && index != 0)
	{
		index = read(fd, temp, BUFFER_SIZE);
		if (index == -1)
		{
			if (str != NULL)
				free(str);
			free(temp);
			return (NULL);
		}
		temp[index] = '\0';
		str = ft_strjoin(str, temp);
	}
	free(temp);
	return (str);
}

char	*str_line(char *str)
{
	int		i;
	char	*s;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			break ;
	if (str[i] == '\n')
		i++;
	s = malloc(sizeof(char) * (i + 1));
	if (s == NULL)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

char	*new_str(char *str)
{
	char	*new_str;
	int		start;
	int		len;
	int		i;

	i = -1;
	while (str[++i])
		if (str[i] == '\n')
			break ;
	if (str[i] == '\n')
		i++;
	start = i;
	len = (ft_strlen(str) - start);
	if (len == 0)
	{
		free(str);
		return (NULL);
	}
	new_str = ft_substr(str, start, len);
	free(str);
	return (new_str);
}

char	*get_next_line(int fd)
{
	static char	*str[10240];
	char		*str2;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	str[fd] = ft_read(str[fd], fd);
	if (str[fd] == NULL || !*str[fd])
	{
		if (str[fd] != NULL)
			free(str[fd]);
		return (NULL);
	}
	str2 = str_line(str[fd]);
	str[fd] = new_str(str[fd]);
	return (str2);
}
