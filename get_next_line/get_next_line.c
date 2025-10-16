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

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize);
size_t	ft_strchr_len(const char *s, int c);
size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize);
char	*exec_before_n(char	*str);

//get_next_line(int fd)
//{
//	static char	*str;
//}

char	*exec_before_n(char	*str)
{
	char	*display;
	char	*tmp;

	if (ft_strchr_len(str, '\n') != 0)
		display = strndup(str, (ft_strchr_len(str, '\n') + 1));
	else
		display = strndup(str, (ft_strchr_len(str, '\0') + 1));
	if (display == NULL)
		return (NULL);
	tmp = strndup(str + ft_strchr_len(str, '\n') + 1,
			ft_strchr_len(str, '\0') - ft_strchr_len(str, '\n'));
	if (!tmp)
		return (free(display), NULL);
	return (display);
}

char	*proceed_after_n(char	*str)
{
	char	*display;
	char	*tmp;

	tmp = strndup(str + ft_strchr_len(str, '\n') + 1,
			ft_strchr_len(str, '\0') - ft_strchr_len(str, '\n'));
	if (!tmp)
		return (free(display), NULL);
	free(str);
	str = tmp;
	return (str);
}

//void	test(void)
//{
//	static char	*str;
//	char		*display;

//	str = "ABC\ndef";
//	str = proceed_after_n(str);
//	printf("%s\n", str);
//}

char	*read_malloc_join(char *str, char *stack, size_t count)
{
	char	*tmp;

	tmp = (char *)malloc(sizeof(char) * (ft_strchr_len(str, '\0') + count + 1));
	ft_strlcpy(tmp, str, ft_strchr_len(str, '\0') + 1);
	if (!*tmp)
		ft_strlcpy(tmp, stack, count + 1);
	else if (*tmp)
		ft_strlcat(tmp, stack, (ft_strchr_len(str, '\0') + count + 1));
	//free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*str;
	char		stack[BUFFER_SIZE];
	size_t		count;
	char		*display;

	if (ft_strchr_len(str, '\n'))
	{
		display = exec_before_n(str);
		str = proceed_after_n(str);
		return (display);
	}
	count = BUFFER_SIZE;
	while (!ft_strchr_len(str, '\n') && count == BUFFER_SIZE)
	{
		count = read(fd, stack, BUFFER_SIZE);
		if (count < BUFFER_SIZE)
			stack[count] = '\0';
		str = read_malloc_join(str, stack, count);
	}
	display = exec_before_n(str);
	str = proceed_after_n(str);
	return (display);
}


size_t	ft_strchr_len(const char *s, int c)
{
	size_t	count;

	count = 0;
	if (!s)
		return (0);
	while (s[count - 1] || count == 0)
	{
		if (s[count] == (char)c)
			return (count);
		count++;
	}
	return (0);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	count;
	size_t	dstlen;


	dstlen = ft_strchr_len(dst, '\0');
	if (!src)
		return (dstlen);
	if (dstsize <= dstlen)
		return (ft_strchr_len(src, '\0') + dstsize);
	count = 0;
	while (src[count] && count + dstlen < dstsize -1)
	{
		dst[dstlen + count] = src [count];
		count++;
	}
	dst[dstlen + count] = '\0';
	return (dstlen + ft_strchr_len(src, '\0'));
}

size_t	ft_strlcpy(char *dst, const char *src, size_t dstsize)
{
	size_t	count;

	count = 0;
	if (!src)
		return (0);
	if (dstsize <= 0)
		return (ft_strchr_len(src, '\0'));
	while (src[count] && count < dstsize -1)
	{
		dst[count] = src [count];
		count++;
	}
	dst[count] = '\0';
	return (ft_strchr_len(src, '\0'));
}

int	main(int argc, char **argv)
{
	int	fd;

	fd = open(argv[1], O_RDONLY);
	//printf("%s", exec_before_n("abcdefghi"));
	//printf("%s\n", read_malloc_join("012", fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	(void)argc;
}
