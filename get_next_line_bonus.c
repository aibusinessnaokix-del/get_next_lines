/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:34:14 by natakaha          #+#    #+#             */
/*   Updated: 2025/10/20 21:31:32 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*exec_before_n(char	*str)
{
	char	*display;

	if (str)
		if (!*str)
			return (NULL);
	if (ft_strchr_len(str, '\n') != -1)
		display = ft_strndup(str, (ft_strchr_len(str, '\n') + 1));
	else
		display = ft_strndup(str, (ft_strchr_len(str, '\0') + 1));
	if (display == NULL)
		return (NULL);
	return (display);
}

char	*proceed_after_n(char	*str)
{
	char	*tmp;

	if (ft_strchr_len(str, '\n') == -1)
	{
		free(str);
		return (NULL);
	}
	tmp = ft_strndup(str + ft_strchr_len(str, '\n') + 1,
			ft_strchr_len(str, '\0') - ft_strchr_len(str, '\n'));
	free(str);
	return (tmp);
}

char	*read_extend_str(int fd, char *str)
{
	long long		count;
	char			*heap;
	char			*tmp;

	count = BUFFER_SIZE;
	while (ft_strchr_len(str, '\n') < 0 && count == BUFFER_SIZE)
	{
		heap = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!heap)
			return (NULL);
		count = read(fd, heap, BUFFER_SIZE);
		if (count >= 0)
		{
			heap[count] = '\0';
			tmp = str;
			str = ft_strjoin(str, heap);
			free(tmp);
		}
		free(heap);

	}
	return (str);
}

char	*get_next_line(int fd)
{
	static char	*str[1024];
	char		*display;

	if (fd == -1 || BUFFER_SIZE == 0)
		return (NULL);
	if (ft_strchr_len(str[fd], '\n') >= 0)
	{
		display = exec_before_n(str[fd]);
		str[fd] = proceed_after_n(str[fd]);
		return (display);
	}
	str[fd] = read_extend_str(fd, str[fd]);
	display = exec_before_n(str[fd]);
	str[fd] = proceed_after_n(str[fd]);
	return (display);
}

//#include <stdio.h>

//int	main(int argc, char **argv)
//{
//	int		fd;
//	char	*display;

//	fd = open(argv[1], O_RDONLY);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s", display);
//	free(display);
//	(void)argc;
//}
