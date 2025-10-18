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
		return (ft_strdup("\0"));
	tmp = ft_strndup(str + ft_strchr_len(str, '\n') + 1,
			ft_strchr_len(str, '\0') - ft_strchr_len(str, '\n'));
	if (!tmp)
		return (NULL);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		*tmp;
	char		stack[BUFFER_SIZE];
	size_t		count;
	char		*display;

	if (fd == -1 || BUFFER_SIZE == 0)
		return (NULL);
	if (ft_strchr_len(str, '\n') != -1)
	{
		display = exec_before_n(str);
		tmp = proceed_after_n(str);
		free(str);
		str = tmp;
		return (display);
	}
	count = BUFFER_SIZE;
	while (ft_strchr_len(str, '\n') == -1 && count == BUFFER_SIZE)
	{
		count = read(fd, stack, BUFFER_SIZE);
		if ((long long int)count < BUFFER_SIZE)
			stack[count] = '\0';
		tmp = ft_strjoin(str, stack);
		free(str);
		str = tmp;
	}
	display = exec_before_n(str);
	tmp = proceed_after_n(str);
	free(str);
	str = tmp;
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
//	printf("%s!", display);
//	free(display);
//	display = get_next_line(fd);
//	printf("%s!", display);
//	free(display);
//	(void)argc;
//}

