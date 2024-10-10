/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbaumgar <mbaumgar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/02 17:40:12 by mbaumgar          #+#    #+#             */
/*   Updated: 2024/07/09 15:27:45 by mbaumgar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// hard limit on open fd : ulimit -n -H return 1048576 on my system

#include "../inc/get_next_line.h"

static char	*get_current_line(char **cached, int critical)
{
	int		i;
	char	*temp;
	char	*next_line;

	i = 0;
	while ((*cached)[i] && (*cached)[i] != '\n')
		i++;
	if ((*cached)[i] == '\n')
		i++;
	next_line = ft_substr(*cached, 0, i, critical);
	temp = ft_substr(*cached, i, ft_strlen(*cached), critical);
	wfree(*cached);
	*cached = temp;
	if (!temp || !next_line || !ft_strlen(next_line))
	{
		wfree(next_line);
		wfree(*cached);
		*cached = NULL;
		return (NULL);
	}
	return (next_line);
}

static char	*start_buffer(char **buffer, char **cached, int critical)
{
	*buffer = (char *)walloc((sizeof(char) * BUFFER_SIZE) + 1, critical);
	if (!(*buffer))
	{
		wfree(*cached);
		*cached = NULL;
		return (NULL);
	}
	return (*buffer);
}

static char	*reading_error(char *buffer, char **cached)
{
	wfree(*cached);
	*cached = NULL;
	return (wfree(buffer), NULL);
}

static void	fill_cache(char *buffer, char **cached, int critical)
{
	char	*temp;

	if (!(*cached))
		*cached = ft_substr(buffer, 0, ft_strlen(buffer), critical);
	else
	{
		temp = ft_strjoin(*cached, buffer, critical);
		wfree(*cached);
		*cached = temp;
	}
}

char	*get_next_line(int fd, int free_static_please, int critical)
{
	int			reading;
	char		*buffer;
	static char	*cached[1048576];

	reading = 1;
	if (cached[fd] && free_static_please)
		return (wfree(cached[fd]), cached[fd] = NULL, NULL);
	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= 1048576)
		return (NULL);
	if (start_buffer(&buffer, &cached[fd], critical) == NULL)
		return (NULL);
	while (reading >= 0)
	{
		ft_bzero(buffer, BUFFER_SIZE + 1);
		reading = read(fd, buffer, BUFFER_SIZE);
		if (reading < 0)
			return (reading_error(buffer, &cached[fd]));
		fill_cache(buffer, &cached[fd], critical);
		if (cached[fd] && (ft_strchr(cached[fd], '\n') || (reading == 0)))
		{
			wfree(buffer);
			return (get_current_line(&cached[fd], critical));
		}
	}
	return (NULL);
}
