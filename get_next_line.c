/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lgeorgia <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/04/27 15:53:52 by lgeorgia          #+#    #+#             */
/*   Updated: 2019/05/04 22:40:50 by lgeorgia         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int		work_with_buf(int fd, char **memory, int file)
{
	char	*help;
	char	buf[BUFF_SIZE + 1];

	while ((file = read(fd, buf, BUFF_SIZE)) > 0)
	{
		buf[file] = '\0';
		if (memory[fd] == NULL)
		{
			if (!(memory[fd] = ft_strnew(1)))
			{
				ft_memdel((void **)&memory[fd]);
				return (-1);
			}
		}
		if (!(help = ft_strjoin(memory[fd], buf)))
		{
			ft_memdel((void **)&memory[fd]);
			return (-1);
		}
		ft_memdel((void **)&memory[fd]);
		memory[fd] = help;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (file);
}

int		ft_norminette(int fd, char **memory, char **line)
{
	if (!(*line = ft_strdup(memory[fd])))
	{
		ft_memdel((void **)&memory[fd]);
		return (-1);
	}
	ft_memdel((void **)&memory[fd]);
	return (1);
}

int		ft_work_with_memory(char **memory, char **line, int fd)
{
	int		i;
	char	*help;

	i = 0;
	while (memory[fd][i] != '\n' && memory[fd][i] != '\0')
		i++;
	if (memory[fd][i] == '\n')
	{
		if (!(*line = ft_strsub(memory[fd], 0, i)))
			return (-1);
		if (!(help = ft_strdup(memory[fd] + i + 1)))
			return (-1);
		ft_memdel((void **)&memory[fd]);
		memory[fd] = help;
		if (memory[fd][0] == '\0')
			ft_memdel((void **)&memory[fd]);
	}
	else if (memory[fd][i] == '\0')
	{
		if (!(ft_norminette(fd, memory, line)))
			return (-1);
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	int			file;
	static char *memory[MAX_FD];

	file = 0;
	if (fd < 0 || line == NULL || fd > MAX_FD)
		return (-1);
	file = work_with_buf(fd, memory, file);
	if (file < 0)
		return (-1);
	else if (file == 0 && (memory[fd] == NULL || memory[fd] == '\0'))
		return (0);
	return (ft_work_with_memory(memory, line, fd));
}
