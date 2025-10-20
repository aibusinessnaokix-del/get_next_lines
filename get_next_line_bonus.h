/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: natakaha <natakaha@student.42tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/10/16 07:34:20 by natakaha          #+#    #+#             */
/*   Updated: 2025/10/20 15:05:04 by natakaha         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include <limits.h>

int		ft_strchr_len(const char *s, int c);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strndup(const char *str, size_t n);
char	*ft_strdup(const char *str);
char	*exec_before_n(char	*str);
char	*proceed_after_n(char	*str);
char	*get_next_line(int fd);

#endif
