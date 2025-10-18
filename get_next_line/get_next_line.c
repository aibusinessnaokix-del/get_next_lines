/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:34:14 by natakaha          #+#    #+#             */
/*   Updated: 2025/10/16 15:39:25 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*exec_before_n(char	*str)
{
	char	*display;

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

	tmp = ft_strndup(str + ft_strchr_len(str, '\n') + 1,
			ft_strchr_len(str, '\0') - ft_strchr_len(str, '\n'));
	if (!tmp)
		return (NULL);
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*tmp;
	char		stack[BUFFER_SIZE];
	size_t		count;
	char		*display;

	if (fd == -1)
		return (NULL);
	if (ft_strchr_len(str, '\n') != -1)
	{
		display = exec_before_n(str);
		str = proceed_after_n(str);
		return (display);
	}
	count = BUFFER_SIZE;
	while (ft_strchr_len(str, '\n') == -1 && count == BUFFER_SIZE)
	{
		count = read(fd, stack, BUFFER_SIZE);
		if (count < BUFFER_SIZE)
			stack[count] = '\0';
		tmp = str;
		str = ft_strjoin(str, stack);
		free(tmp);
	}
	display = exec_before_n(str);
	str = proceed_after_n(str);
	return (display);
}

#include <stdio.h>

int	main(int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	printf("%d\n", fd);
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	//printf("%s", get_next_line(fd));
	(void)argc;
}

